#include <stdio.h>

#include "random.h"


/* Simple Park-Miller */

#ifndef NO_THREAD_LOCAL

static __thread unsigned long pmseed = 29264;

void
fast_srandom(unsigned long seed_)
{
	pmseed = seed_;
}

unsigned long
fast_getseed(void)
{
	return pmseed;
}

uint16_t
fast_random(unsigned int max)
{
	unsigned long hi, lo;
	lo = 16807 * (pmseed & 0xffff);
	hi = 16807 * (pmseed >> 16);
	lo += (hi & 0x7fff) << 16;
	lo += hi >> 15;
	pmseed = (lo & 0x7fffffff) + (lo >> 31);
	return ((pmseed & 0xffff) * max) >> 16;
}

float
fast_frandom(void)
{
	/* Construct (1,2) IEEE floating_t from our random integer */
	/* http://rgba.org/articles/sfrand/sfrand.htm */
	union { unsigned long ul; floating_t f; } p;
	p.ul = (((pmseed *= 16807) & 0x007fffff) - 1) | 0x3f800000;
	return p.f - 1.0f;
}

#else

/* Thread local storage not supported through __thread,
 * use pthread_getspecific() instead. */

#include <pthread.h>

static pthread_key_t seed_key;

static void __attribute__((constructor))
random_init(void)
{
	pthread_key_create(&seed_key, NULL);
	fast_srandom(29264UL);
}

void
fast_srandom(unsigned long seed_)
{
	pthread_setspecific(seed_key, (void *)seed_);
}

unsigned long
fast_getseed(void)
{
	return (unsigned long)pthread_getspecific(seed_key);
}

uint16_t
fast_random(unsigned int max)
{
	unsigned long pmseed = (unsigned long)pthread_getspecific(seed_key);
	unsigned long hi, lo;
	lo = 16807 * (pmseed & 0xffff);
	hi = 16807 * (pmseed >> 16);
	lo += (hi & 0x7fff) << 16;
	lo += hi >> 15;
	pmseed = (lo & 0x7fffffff) + (lo >> 31);
	pthread_setspecific(seed_key, (void *)pmseed);
	return ((pmseed & 0xffff) * max) >> 16;
}

unsigned long random_init_omp(unsigned long * seed)
{
	*seed = *seed * 29264UL;
	fast_frandom_omp(seed);
	return *seed;
}

float
fast_frandom_omp(unsigned long * seed)
{
	/* Construct (1,2) IEEE floating_t from our random integer */
	/* http://rgba.org/articles/sfrand/sfrand.htm */
	unsigned long pmseed = *seed;
	pmseed *= 16807;
	union { unsigned long ul; floating_t f; } p;
	p.ul = ((pmseed & 0x007fffff) - 1) | 0x3f800000;
	*seed = pmseed;
	return p.f - 1.0f;
}

uint16_t
fast_random_omp(unsigned int max, unsigned long * seed)
{
	unsigned long pmseed = *seed;
	unsigned long hi, lo;
	lo = 16807 * (pmseed & 0xffff);
	hi = 16807 * (pmseed >> 16);
	lo += (hi & 0x7fff) << 16;
	lo += hi >> 15;
	pmseed = (lo & 0x7fffffff) + (lo >> 31);
	*seed = pmseed;
	return ((pmseed & 0xffff) * max) >> 16;
}


float
fast_frandom(void)
{
	/* Construct (1,2) IEEE floating_t from our random integer */
	/* http://rgba.org/articles/sfrand/sfrand.htm */
	unsigned long pmseed = (unsigned long)pthread_getspecific(seed_key);
	pmseed *= 16807;
	union { unsigned long ul; floating_t f; } p;
	p.ul = ((pmseed & 0x007fffff) - 1) | 0x3f800000;
	pthread_setspecific(seed_key, (void *)pmseed);
	return p.f - 1.0f;
}

#endif
