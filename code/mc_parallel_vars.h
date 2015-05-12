#ifndef MONTE_CARLO_PARALLEL_VARS
#define MONTE_CARLO_PARALLEL_VARS
#include <stdio.h>
#include "mpi.h"

extern int omp_thread_count;
extern int total_game_count_mc_original;
extern int total_game_count_mc_omp;
extern int total_game_count_mc_mpi;

void print_game_stats(void);

#endif
