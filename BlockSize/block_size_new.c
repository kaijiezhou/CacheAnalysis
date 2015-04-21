#include <stdio.h>
#include <sys/time.h>
#define WRITE_DATA_SIZE 25 
#define MAX_SLOT 5 
#define READ_DATA_SIZE 256
#define LOOP_NUMBER 10
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
int writeData(int *data){
    memset(data,0,1<<(WRITE_DATA_SIZE-2));
    return 0;
}

int readData(int *data, int size, int slot){
    int i,temp;
    counter_start();
    for(i =0;i<size;i++){
        (*(data + i * slot))++;
    }
    counter_stop();
    printf("%d %u\n",slot,c2-c1);
    return 0;
}
int main(){
        int count;
        for(count = 0; count<LOOP_NUMBER;count++){
        printf("************\n");
        int *data ;
        unsigned adj;
        adj = 32 - ((unsigned)data%32);
        data = data +adj;
        data= (int *)malloc(sizeof(int) * (1 <<WRITE_DATA_SIZE-2)+64);
        writeData(data);
        readData(data,READ_DATA_SIZE,1 << MAX_SLOT);
        int i;
        for(i = 0; i < MAX_SLOT;i++){
        readData(data + ((i+1) * (1 << MAX_SLOT) * READ_DATA_SIZE) ,READ_DATA_SIZE,(1 << i));
        }
        free(data);
        }
        return 0;
}
      

