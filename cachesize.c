#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<sys/time.h>
#define LOOPNUMBER 100

unsigned long readCache(int *a, long start, long end){
        int i; //iterator
        int tmp; //temp data
        struct timeval sc;//start time
        struct timeval ec;//end time

        gettimeofday(&sc,NULL);
        for(i=start;i<end;i++){
                tmp=a[i];
        }
        gettimeofday(&ec,NULL);

        unsigned long time = 1000000 * (ec.tv_sec - sc.tv_sec) + ec.tv_usec - sc.tv_usec;
        //printf("Run time of walking %ld-%ld is %ld usec\n",start,end,time);
        return time;
}

void calculateTime(int size){
        long length=size;
        long indexAt8K=size/2;

        /*long cacheLength=pow(2,20)/4;// length = 16K
        int *a=(int *)malloc(sizeof(int)*cacheLength);
        long i;
        for(i=0;i<cacheLength;i++){
                a[i]=0;
        }*/

        long t1 = 0;
        long t2 = 0;
        long t3 = 0;
        int i =0;
        for(i = 0;i < LOOPNUMBER;i++){

        long cacheLength=pow(2,20)/4;// length = 16K
        int *a=(int *)malloc(sizeof(int)*cacheLength);
        long j;
        for(j=0;j<cacheLength;j++){
                a[j]=0;
        }
t1=readCache(a,0,indexAt8K);
                t2=readCache(a,indexAt8K,length);
                t3=readCache(a,0,indexAt8K);
        printf("%d %d %d\n", t1,t2,t3);
        }
        double result = ((double)(t1 - t3)) / ((double) t1);
        //printf("Size = %ld , (T1-T3)/T1 = %f\n",size,result);
        //printf("%d %d %d\n", t1,t2,t3);
}

int main(){
        //int i;
        //for(i = 2; i <= 20;i++){
                long cacheLength = pow(2,(double)14)/4;// length = 16K
                calculateTime(cacheLength);
        //}
        return 1;
}

