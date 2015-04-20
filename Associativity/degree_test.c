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

unsigned c1, c2 ;

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
    unsigned c=0;
    for(i = 0;i < length / 4; i++){
        counter_start();
        temp = *(data + i * 4);
        counter_stop();
        c += c2-c1;
    }
    printf("%d %d %u\n", initial, initial + length ,c);
    return 0;
}

int main(){
    int *data1 = (int *)malloc(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i;
    for(i = 1 ; i <= 3;i++){
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

