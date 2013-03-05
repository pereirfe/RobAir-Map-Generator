/* System's Configurantion Parameters for the mapping  *
 * By Fernando Pereira                                 *
 * mars 5 2013                                         */

#ifndef __MAPPING__
#define __MAPPING__

#include <time.h>
#include <sys/time.h>
#include "config.h"

#define GRAY  195
#define WHITE 254
#define DIM_F 4000 

#define PERSON_SIZE (PIX_PER_M*TIME_C_INIT*SPEED_H*(1+SECURITY_MARGIN)/100)
#define PERSON_SIZE_RADIUS (PIX_PER_M*time_dyn*SPEED_H*(1+SECURITY_MARGIN)/100) 



#endif
