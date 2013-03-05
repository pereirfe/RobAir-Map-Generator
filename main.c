#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#define GRAY  195
#define WHITE 254
#define DIM_F 4000 

#define MAX_IT 10.0

#define SPEED_H 1 // m/s
#define TIME_C_INIT 3 // s
#define PIX_PER_M 100 // Example
#define PERSON_SIZE (PIX_PER_M*TIME_C_INIT*SPEED_H)
#define PERSON_SIZE_RADIUS (PIX_PER_M*time_dyn*SPEED_H) 

#define ADDR_MAP "map_test3.pgm"
#define ADDR_POINTS "points.txt"

double  time_dyn = TIME_C_INIT; // Time dynamic for calculus of size
// Heuristic: TIME_C_INIT(t) >> time_dyn(t) for t > 0.
// An adjustment may be necessary

#define POINT_MAX 10 // Max number of coordinates that may be used to localize a person

typedef struct{
  int x, y;
} Point;

void create_map(char**, char**, char[][PERSON_SIZE], Point*, int);
void handler_map(void);
void init_map_teamplate(char**);
void init_person_teamplate(char p[][PERSON_SIZE]);
void fill_points(Point* );

int main(void){
  time_t tstart, tend;
  struct timeval clk1, clk2;
  int i, total;
  char* var[DIM_F], *fix[DIM_F];
  char person[PERSON_SIZE][PERSON_SIZE];

  Point points[POINT_MAX];
  int qt = 0;

  for(i=0; i<DIM_F; i++){ // Create the two maps
    var[i] = (char*)(malloc(sizeof(char)*DIM_F));
    fix[i] = (char*)(malloc(sizeof(char)*DIM_F));
    if(! (var[i] || fix[i])){
      puts("NO MEM!!");
      return;
    }
  }

  for(i=0; i<POINT_MAX; i++){
    points[i].x = rand() % DIM_F;
    points[i].y = rand() % DIM_F;
  }
  
  init_map_teamplate(fix);
  init_person_teamplate(person);
  srand(time(0));
  printf("CLOCKS_PER_SEC = %d\n", CLOCKS_PER_SEC);

  tstart = time(0);
  for(i=0; i<MAX_IT; i++){
    time_dyn = (double)((clk2.tv_sec + clk2.tv_usec/1000000.0) - (clk1.tv_sec + clk1.tv_usec/1000000.0));
    gettimeofday(&clk1, NULL);
    
    fill_points(points); // Get from a file // TO IMPLEMENT

    if( (int) PERSON_SIZE_RADIUS <= PERSON_SIZE ) { 
      init_person_teamplate(person); 
    }
    
    printf("PERSON_SIZE_RADIUS: %d -- time_dyn = %f\n", (int)PERSON_SIZE_RADIUS,time_dyn);
    
    create_map(var, fix, person, points, POINT_MAX);
    if(!(i%50)) printf("i: %d\n", i);
    gettimeofday(&clk2, NULL);
  }
  tend = time(0);

  total = difftime(tend, tstart);
  printf("Tot: %d\nMean: %f\n", total, (float)(total)/MAX_IT);
}

void create_map(char** var, char** fix, char p[][PERSON_SIZE], Point* points, int qt){
  int i, j, k, x, y;
  int x_wr, y_wr;
  FILE* f;
  
  for(i=0; i<DIM_F; i++){ // Copy of the original map to the new one
    for(j=0; j<DIM_F; j++){
      var[i][j] = fix[i][j];
    }
  }
  
  // Add persons
  for(i=0; i<qt; i++){
    x = points[i].x - (PERSON_SIZE/2); // Check borders
    x = (x<0? 0:x);
    
    y = points[i].y - (PERSON_SIZE/2); // Check borders
    y = (y<0? 0:y);
    
    for(j=0; j<(PERSON_SIZE); j++){
      for(k=0; k<(PERSON_SIZE); k++){
	x_wr = (j + x);
	y_wr = (k + y);
	if( (x_wr >= DIM_F) || (y_wr >= DIM_F) ) continue; // Out of borders

	// keep the gray from whoever have it (?)
	var[x_wr][y_wr] = ( (var[x_wr][y_wr] < p[j][k]) ? var[x_wr][y_wr]:p[j][k] );   
      }
    }
  }

  if( !(f = fopen(ADDR_MAP, "wb")) ) { 
    printf("NO FILE!!!!\n");
    return;
  }
  
  // P5 = PGM Bitmap
  // 4000 x 4000 pixels
  // full-white =  255
  fprintf(f, "P5\n4000 4000\n255\n"); 

  for(i=0; i<DIM_F; i++){
    fwrite(var[i], sizeof(char), DIM_F, f); 
  }
  fclose(f);
}


void init_person_teamplate(char p[][PERSON_SIZE]){
  int c, radius_sq;
  int i, j;

  radius_sq = (int)PERSON_SIZE_RADIUS;
  c = PERSON_SIZE/2;
  radius_sq*=radius_sq;

  for(i=0; i<PERSON_SIZE; i++){
    for(j=0; j<PERSON_SIZE; j++){
      if( ((i-c)*(i-c) + ((j-c)*(j-c))) < radius_sq) { 
	p[i][j] = GRAY; 
      }
      else p[i][j] = WHITE;
    }
  }
}


void init_map_teamplate(char** fix){
  int i, j;
  if(fix == NULL) return;

  for(i=0; i<DIM_F; i++){
    for(j=0; j<DIM_F; j++){
        if( (i>200) && (i<3800) && (j>200) && (j<3800) ) // Test map.
	fix[i][j] = WHITE;
         else fix[i][j] = GRAY;
    }
  }
}

void fill_points(Point* p){
  int i;
  FILE * f; 

  do {
    f = fopen(ADDR_POINTS, "r");
    printf("Waiting...\n");
  } while (f==NULL); 
  
  for(i=0; i<POINT_MAX; i++){
    fscanf(f, " %d %d\n", &p[i].x, &p[i].y); 
  }
  fclose(f);
}
