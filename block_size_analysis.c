#include <stdio.h>
#include <time.h>
int main(){
	time_t start,end;
	start = time(NULL);
	printf("hello");
	printf(" world!!!!\n");
	end = time(NULL);
	printf("The time is %f\n",difftime(end,start));
	return 1;
}
