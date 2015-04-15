nclude <stdio.h>
#include <sys/time.h>
#define WRITE_DATA_SIZE 25
#define MAX_SLOT 5
#define READ_DATA_SIZE 256
#define LOOP_NUMBER 100
int writeData(int *data){
    memset(data,0,1<<(WRITE_DATA_SIZE - 2));
    return 0;
}

int readData(int *data, int size, int slot){
    int i,temp;
    struct timeval sc,tc;
    gettimeofday(&sc,NULL);
    for(i =0;i<size;i++){
        temp = *(data + i * slot);
    }
    gettimeofday(&tc,NULL);
    unsigned long time = 1000000 * (tc.tv_sec - sc.tv_sec) + tc.tv_usec -
        sc.tv_usec;
    printf("%d %ld\n",slot << 2,time);
    return 0;
}

int main(){
        int count;
        for(count = 0; count<LOOP_NUMBER;count++){
        printf("************\n");
        int *data = (int *)malloc(sizeof(int) * 1<<(WRITE_DATA_SIZE - 2));
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

