#include <stdio.h>
#include <sys/time.h>

#define WRITE_DATA_SIZE 23
#define CACHE_SIZE 14

int readData(int *data, int length){
    int i,temp;
    for(i = 0;i < length ; i++){
        temp = *(data + i);
    }
    return 0;
}

int calculateTime(int *data, int log_of_associativity){
    long dataNumber = 1 << (CACHE_SIZE - log_of_associativity);
    struct timeval sc,tc;
    int associativity = 1 << (log_of_associativity - 1);
    int i;
    for(i = 0; i < associativity + 1;i++){
        gettimeofday(&sc,NULL);
        readData(data + 2 * i * dataNumber, dataNumber);
        gettimeofday(&tc,NULL);
        unsigned long time = 1000000 * (tc.tv_sec - sc.tv_sec) + tc.tv_usec 
                - sc.tv_usec;                                 
        printf("%d %d %ld\n", 2 * i * dataNumber, 2 * i * dataNumber +       
                dataNumber ,time);                            
    }                                                         
    gettimeofday(&sc,NULL);                                   
    readData(data,dataNumber);                                
    gettimeofday(&tc,NULL);                                   
    unsigned long time = 1000000 * (tc.tv_sec - sc.tv_sec) + tc.tv_usec     
        - sc.tv_usec;                                         
    printf("%d %d %ld\n",0 ,dataNumber ,time);                
    return 0;                                                 
}                                                             
                                                              
int main(){                                                   
    int *data = (int *)malloc(sizeof(int) * (1 << WRITE_DATA_SIZE));        
    int i;                                                    
    for(i = 1 ; i <= 3;i++){                                  
        memset(data,0,(1 << WRITE_DATA_SIZE));                
        calculateTime(data,i);                                
        printf("\n");                                         
    }                                                         
    return 0;                                                 
} 