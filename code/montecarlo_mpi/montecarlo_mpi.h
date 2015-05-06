#ifndef PACHI_montecarlo_mpi_montecarlo_mpi_H
#define PACHI_montecarlo_mpi_montecarlo_mpi_H

#include "engine.h"

struct engine *engine_montecarlo_mpi_init(char *arg, struct board *b);

#endif
