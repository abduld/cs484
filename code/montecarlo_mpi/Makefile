INCLUDES=-I..
OBJS=montecarlo_mpi.o

all: montecarlo_mpi.a
montecarlo_mpi.a: $(OBJS)

clean:
	rm -f *.o *.a
clean-profiled:
	rm -f *.gcda *.gcno

-include ../Makefile.lib
