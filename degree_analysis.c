#include <stdio.h>
#include <sys/time.h>

#define WRITE_DATA_SIZE 23
#define CACHE_SIZE 14
#define BLOCK_SIZE 4
static inline unsigned ccnt_read (void)
{
      unsigned cc;
        __asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
          return cc;
}

unsigned c1, c2;

void counter_start(void)
{
      c1 = ccnt_read();
}

void counter_stop(void)
{
      c2 = ccnt_read();
}

void counter_print(void)
{
      printf("c1 = %u\n", c1);
        printf("c2 = %u\n", c2);
          printf("c2 - c1 = %u\n", c2 - c1);
}


int readData(int *data,int initial, int length){
    int i,temp;
    struct timeval sc,tc;
   // gettimeofday(&sc,NULL);
    counter_start();
    for(i = 0;i < length / 4; i++){
        temp = *(data + i * 4);
    }
    /*gettimeofday(&tc,NULL);
    unsigned long time = 1000000 * (tc.tv_sec - sc.tv_sec) + tc.tv_usec
        - sc.tv_usec;*/
    counter_stop(); 
    printf("%d %d %u\n", initial, initial + length ,c2-c1);
    return 0;
}

int calculateTime(int *data, int log_of_associativity){
    long dataNumber = 1 << (CACHE_SIZE - log_of_associativity);
    long dataSize = dataNumber>>2;
    int associativity = 1 << (log_of_associativity - 1);
    int i;
    for(i = 0; i < associativity + 1;i++){
        readData(data + 2 * i * dataNumber,2 * i * dataNumber, dataSize);
    }
    readData(data,0,dataSize);
    readData(data,0,dataSize);
    return 0;
}

int main(){
    int *data = (int *)malloc(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int *data1 = (int *)malloc(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i;
    for(i = 1 ; i <= 3;i++){
        //memset(data,0,(1 << WRITE_DATA_SIZE));
        readData(data1,0,(1<<WRITE_DATA_SIZE));
        printf("\n");
        calculateTime(data,i);
        printf("\n");
    }
    return 0;
}

