#include<stdio.h>
#include<malloc.h>
#define LOOPNUMBER 100
#define CACHESIZE 14
#define DATASIZE 20
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
unsigned readData(int *data, long length){
        int i; //iterator
        counter_start();
        for(i=0 ;i<length/8 ;i++){
            (*(data + i*8))++;
        }
        counter_stop();
        return c2-c1;
}

void calculateTime(){
    long cacheSize = 1 << (CACHESIZE -2);
    long dataSize = 1 << DATASIZE;
    int *data = (int *)malloc(sizeof(int)*dataSize);
    memset(data,0,cacheSize);
    readData(data,dataSize);
    unsigned t1 = readData(data,cacheSize>>1);
    unsigned t2 = readData(data +(cacheSize>>1),cacheSize>>1);
    unsigned t3 = readData(data,cacheSize>>1);
    printf("%10u   %10u   %10u\n", t1,t2,t3);
}
int main(){
    int i;
    for(i = 0;i< LOOPNUMBER;i++)
        calculateTime();
        return 1;
}
