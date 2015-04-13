#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
	time_t start,end;
	struct timespec tstart={0,0},tend={0,0};
	start = time(NULL);
	clock_gettime(CLOCK_MONOTONIC,&tstart);
	int* p = malloc(1024 * 1024 * 100 / 4 * sizeof(int));
	memset(p,0,1024 * 1024 * 25);
	long i =0;
	for(i = 0;i<1024;i++){
	    printf("%ld->%d\n",i,(*(p + i * 1024 * 25)));
	}
	printf("hello");
	printf("DWTSB");
	printf("DWTBigSB");
	end = time(NULL);
	clock_gettime(CLOCK_MONOTONIC,&tend);
	printf("The time is %f\n",difftime(end,start));
	return 1;
}
