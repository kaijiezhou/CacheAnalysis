#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<sys/time.h>
#define LOOPNUMBER 100
static inline unsigned ccnt_read (void)
{
      unsigned cc;
        __asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
          return cc;
}

unsigned c1, c2 ;

void counter_start(void)
{
      c1 = ccnt_read();
}

void counter_stop(void)
{
      c2 = ccnt_read();
}
unsigned readCache(int *a, long start, long end){
        int i; //iterator
        int tmp; //temp data
        counter_start();
        for(i=start;i<end;i++){
                tmp=a[i];
        }
        counter_stop();
        return c2-c1;
}

void calculateTime(int size){
        long length=size;
        long indexAt8K=size/2;

        unsigned t1 = 0;
        unsigned t2 = 0;
        unsigned t3 = 0;
        int i =0;
        for(i = 0;i < LOOPNUMBER;i++){

        long cacheLength=pow(2,20)/4;// length = 16K
        int *a ;
        unsigned adj;
        adj = 32 - ((unsigned)a%32);
a = a +adj;
        a=(int *)malloc(sizeof(int)*cacheLength);
        long j;
        for(j=0;j<cacheLength;j++){
                a[j]=0;
        }
        t1=readCache(a,0,indexAt8K);
        t2=readCache(a,indexAt8K,length);
        t3=readCache(a,0,indexAt8K);
        printf("%10u   %10u   %10u\n", t1,t2,t3);
        }
}

int main(){
        long cacheLength = pow(2,(double)14);// length = 16K
        calculateTime(cacheLength);
        return 1;
}

