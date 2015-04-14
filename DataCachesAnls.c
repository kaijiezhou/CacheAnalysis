#include<stdio.h>
#include<math.h>
#include<time.h>
//#include<malloc.h>

double readCache(int *a, long start, long end){
	int i,tmp;
	clock_t sc,ec;
	sc=clock();
	for(i=start;i<end;i++){
		tmp=a[i];
	}
	ec=clock();
	double t=(double)(ec-sc)/CLOCKS_PER_SEC;
	printf("run time of walking %ld-%ld is %f sec\n",start,end,t);
	return t;
}

int main(){
	long length=pow(2,14)/4;
	long indexAt8K=pow(2,13)/4;
	int *a=(int *)malloc(sizeof(int)*length);
	int *b=(int *)malloc(sizeof(int)*length);
	long i;
	for(i=0;i<length;i++){
		a[i]=0;
	}
	for(i=0;i<length;i++){
		b[i]=1;
	}
	double t1=readCache(a,0,indexAt8K);
	double t2=readCache(a,indexAt8K,length);
	double t3=readCache(a,0,indexAt8K);
	if (t1==t3)
		printf("Size of Data Cache is 8K!\n");
	else 
		printf("Size of Data Cache is 16K!\n");
	return 1;
}
