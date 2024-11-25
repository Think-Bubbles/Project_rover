#include "times.h"

clock_t start_time()
{
    clock_t start = clock();
    return start;
}

clock_t end_time()
{
    clock_t end = clock();
    return end;
}

void print_time(clock_t start, clock_t end)
{
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);
    printf("Time taken: %f milliseconds\n", time_taken * 1000);
}