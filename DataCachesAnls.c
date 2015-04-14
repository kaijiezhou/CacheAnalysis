#include<stdio.h>
#include<math.h>
#include<time.h>
#include<malloc.h>

long readCache(int *a, long start, long end){
	int i,tmp;
	clock_t sc,ec;
	sc=clock();
	for(i=start;i<end;i++){
		tmp=a[i];
	}
	ec=clock();
	long t=(long)(ec-sc);
	printf("run time of walking %ld-%ld is %ld cycles\n",start,end,t);
	return t;
}

int main(){
	long length=pow(2,14)/4;
	long indexAt8K=pow(2,13)/4;
	clock_t start,end;
	int *a=(int *)malloc(sizeof(int)*length);
	int *b=(int *)malloc(sizeof(int)*length);
	long i;
	start=clock();
	for(i=0;i<length;i++){
		a[i]=0;
	}
	end=clock();
	printf("first go a[]: %ld cycles\n",end-start);
	start=clock();
	for(i=0;i<length;i++){
		b[i]=1;
	}
	end=clock();
	printf("second go b[]:%ld cycles\n", end-start);
	long t1=readCache(a,0,indexAt8K);
	long t2=readCache(a,indexAt8K,length);
	long t3=readCache(a,0,indexAt8K);
	//if (t1==t3)
	//	printf("Size of Data Cache is 8K!\n");
	//else 
	//	printf("Size of Data Cache is 16K!\n");
	return 1;
}