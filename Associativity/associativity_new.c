#include <stdio.h>
#include <sys/time.h>

#define WRITE_DATA_SIZE 23
#define CACHE_SIZE 14
#define BLOCK_SIZE 4
#define TIMES 100000
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

int readData(int *data,int initial, int length){
    int i;
    //struct timeval sc,tc;
    //unsigned c=0;
    for(i = 0;i < length ; i++){
        //counter_start();
        (*(data + i))++;
        //counter_stop(); 
        //c += c2-c1;
    }
    //printf("%d %d %u\n", initial, initial + length ,c);
    return 0;
}

int calculateTime(int *data, int log_of_associativity){
    long dataNumber = 1 << (CACHE_SIZE - log_of_associativity);
    long dataSize = 1;
    //long dataSize = 1<<2;
    int associativity = 1 << (log_of_associativity);
    int i,counter;
    counter_start();
for(counter = 0; counter < TIMES;counter++){
    for(i = 0; i < associativity;i++){                                                                                                                             
        readData(data + 2 * i * dataNumber,2 * i * dataNumber, dataSize);
    }
    }
    counter_stop();
    double c = c2 -c1;
    double times = TIMES * associativity;
    printf("%d %f\n", log_of_associativity,c / times   );
    //readData(data,0,dataSize);
    //readData(data,0,dataSize);
    return 0;
}


int main(){
    int *data1 = (int *)malloc(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i;
    for(i = 1 ; i <= 5;i++){
        void *p;
        int *data_i ;
        p = malloc(sizeof(int) * (1 <<WRITE_DATA_SIZE)+64);
        unsigned adj;
        adj = 32 - ((unsigned)p%32);
        p = p +adj;
        data_i = (int *) p;

        memset(data_i,0,(1 << WRITE_DATA_SIZE));
        memset(data1,0,(1 << WRITE_DATA_SIZE));

        //readData(data_i,0,(1<<WRITE_DATA_SIZE));
        printf("\n");
        calculateTime(data_i,i);
        printf("\n");
    }
    return 0;
}

