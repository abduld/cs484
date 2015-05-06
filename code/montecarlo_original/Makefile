INCLUDES=-I..
OBJS=montecarlo_original.o

all: montecarlo_original.a
montecarlo_original.a: $(OBJS)

clean:
	rm -f *.o *.a
clean-profiled:
	rm -f *.gcda *.gcno

-include ../Makefile.lib
