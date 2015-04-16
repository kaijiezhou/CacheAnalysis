//#include <stdio.h>
//#include <sys/time.h>
//#include <malloc.h>
#include <alloca.h>

#define WRITE_DATA_SIZE 23
#define CACHE_SIZE 14
#define BLOCK_SIZE 4

int readData(int *data,int initial, int length){
    int i,temp;
//    struct timeval sc,tc;
//    gettimeofday(&sc,NULL);
    for(i = 0;i < length / 4; i++){
        temp = *(data + i * 4);
    }
//    gettimeofday(&tc,NULL);
//    unsigned long time = 1000000 * (tc.tv_sec - sc.tv_sec) + tc.tv_usec
//        - sc.tv_usec;
    //printf("%d %d %ld\n", initial, initial + length ,time);
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
int degreeCalculateTime(){
    int *data = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int *data1 = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i;
    for(i = 1 ; i <= 3;i++){
        //memset(data,0,(1 << WRITE_DATA_SIZE));
        readData(data1,0,(1<<WRITE_DATA_SIZE));
        //printf("\n");
        calculateTime(data,i);
        //printf("\n");
    }
    return 0;
}
int main(){
    int *data = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int *data1 = (int *)alloca(sizeof(int) * (1 << WRITE_DATA_SIZE));
    int i;
    for(i = 1 ; i <= 3;i++){
        //memset(data,0,(1 << WRITE_DATA_SIZE));
        readData(data1,0,(1<<WRITE_DATA_SIZE));
        //printf("\n");
        calculateTime(data,i);
        //printf("\n");
    }
    return 0;
}

