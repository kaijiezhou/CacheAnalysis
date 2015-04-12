/*
 * Prog1.c
 *
 *  Created on: Apr 11, 2015
 *      Author: kaijiezhou
 */
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<malloc.h>
void init(int *a,long length){
	int i;
	clock_t start,end;
	start=clock();
	for (i=0;i<length;i++){
		a[i]=0;
	}
	end=clock();
	double spent=(double)(end - start)/ CLOCKS_PER_SEC;
	printf("Running time of init is: %f sec\n", spent);
}

void addOne(int *a,long length){
	int i;
	clock_t start,end;
	start=clock();
	for (i=0;i<length;i++){
		a[i]++;
	}
	end=clock();
	double spent=(double)(end - start) / CLOCKS_PER_SEC;
	printf("Running time of add one is: %f sec\n", spent);
}
int main(){
	long length =(100*pow(2,20))/4;
	int *a= (int *)malloc(sizeof(int)*length);
	init(a,length);
	addOne(a,length);
	return 1;
}

