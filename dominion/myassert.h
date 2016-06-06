#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void check_functions(int func){
	if(!(func == 1 || func == 0)){
		printf("TEST FAILED: Function Crashed for Returning '-1'\n\n");
		exit(0);
	}
}

void check_equal(int a, int b){
	if(a != b){
		printf("TEST FAILED: Parameters not equal\n\n");
		exit(0);
	}
	printf("Parameters are Equal\n\n");
}

