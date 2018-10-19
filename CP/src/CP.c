/*
 ============================================================================
 Name        : CP.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void *f(void *arg)
{
	float *counter = (float *)malloc(sizeof(float));
	int *actual_arg = arg;
	int i;
    unsigned int seed = time(NULL);
	printf("Value:  %d\n", *actual_arg);
	for(i = 0;i<*actual_arg;i++) {
				float x = (float)rand_r(&seed)/RAND_MAX;
				float y = (float)rand_r(&seed)/RAND_MAX;
				float dist = (x*x) + (y*y);
				if(dist < 1) *counter+=1;
	    	}
	return (void *) counter;
}

int main()
{
	clock_t begin = clock();
	int ntimes = 4;
	long nPoints = 1000000000;
	int x = nPoints/ntimes;
	float nPointsCircle = 0;
	void *r;
	int i;

	pthread_t *tid = malloc( ntimes * sizeof(pthread_t) );

	for( i=0; i<ntimes; i++ )
		pthread_create( &tid[i], NULL, f, &x);


	for( i=0; i<ntimes; i++ ){
		pthread_join( tid[i], &r );
		nPointsCircle += *(float *)r;
	}
	free(r);
	double value = (double) nPointsCircle/nPoints;
	printf("Value:  %f\n", nPointsCircle);
    printf("Value for Pi is %f \n", 4.0*value);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Value for Time is %f \n", time_spent);
}
