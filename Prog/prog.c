#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WRITE_DATA_SIZE 20
#define BLOCK_SIZE 4

static inline unsigned ccnt_read (void)
{
      unsigned cc;
        __asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
          return cc;
}

unsigned c1, c2, time;

void counter_start(void)
{
      c1 = ccnt_read();
}

void counter_stop(void)
{
      c2 = ccnt_read();
        time += (c2 - c1) / 100000;
}

void counter_print(void)
{
    printf("%d\n", time);      
}

void write_prog1(int *data, int loopNumner, int size){
    int i,j;
    for(i = 0;i<loopNumner;++i){
        reset();
        counter_start();
        for (int j = 0; j < size; ++j)
        {
            (*(data + j))++;
        }
        counter_stop();
    }
    counter_print();
    return;
}

void write_prog2(int *data, int loopNumner, int size){
    int i,j;
    for(i = 0;i<loopNumner;++i){
        reset();
        for (int k = 0; k < 8; ++k)
        {
            counter_start();
            for (int j = k; j < size; j=j+8)
            {
                (*(data + j))++;
            }
            counter_stop();
        }
    }
    counter_print();
    return;
}

void freshMemory(int *data, int size){
    for (int j = 0; j < size; ++j){
            *(data + j) = 0;;
        }
}
int main(int argc, char *argv[]){
	time = 0;
    int j;
    int *data ;
    unsigned adj;
    adj = 32 - ((unsigned)data%32);
    data = data +adj;
    data= (int *)alloca(sizeof(int) * (1 <<(WRITE_DATA_SIZE-2)) * 10 +64);
    int arrary_size = (1 <<(WRITE_DATA_SIZE-2)) * 10;
    init_ccr();
    for(j = 1; j<=1000; j = j*10){
        freshMemory(data,arrary_size);
        write_prog1(data,j,arrary_size);
        freshMemory(data,arrary_size);
        write_prog2(data,j,arrary_size);
    }
    return 0;
}
