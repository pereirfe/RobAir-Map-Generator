/* Configurantion Parameters for the mapping system    *
 * Any changement here shouldn't destroy the program   *
 *                                                     *
 * By Fernando Pereira                                 *
 * mars 5 2013                                         */

#ifndef __MAPPING__CONFIG__
#define __MAPPING__CONFIG__

#define MAX_IT 10 // Number of iterations in the main loop
#define SPEED_H 1 // Mean speed of a human being (in a museum), in m/s
#define TIME_C_INIT 3 //Initial overestimated calculus time, in s
#define PIX_PER_M 100 // Size of the map, Example
#define SECURITY_MARGIN 50 // in %

#define ADDR_MAP "map_test3.pgm" // File's Address with map
#define ADDR_POINTS "points.txt" // File's Address with points

#define POINT_MAX 10 // Max number of coordinates that may be used to localize people

#endif
