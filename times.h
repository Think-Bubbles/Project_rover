#ifndef PROJECT_ROVER_TIMES_H
#define PROJECT_ROVER_TIMES_H
#include <time.h>
#include <stdio.h>

/**
 * Records the current time as the start time.
 * Returns: The recorded start time.
 */
clock_t start_time();

/**
 * Records the current time as the end time.
 * Returns: The recorded end time.
 */
clock_t end_time();

/**
 * Prints the time elapsed between the start and end times.
 * Parameters:
 *  - start: The recorded start time.
 *  - end: The recorded end time.
 */
void print_time(clock_t start, clock_t end);

#endif //PROJECT_ROVER_TIMES_H
