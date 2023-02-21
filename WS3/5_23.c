#include <stdio.h>

int main(void) {

	const int MAX_NUMS = 20;
	int lower;
	int lowest;
	int array[MAX_NUMS];
	int num;

	scanf("%d", &num);
	for(int i =0; i < num; i++){
		scanf("%d", &array[i]);
	}

	if(array[0] <= array[1]){
		lowest = array[0];
		lower = array[1];
	}
	else{
		lowest = array[1];
		lower = array[0];
	}

	for(int i = 2; i < num; i++){
		if(array[i] < lower && array[i] < lowest){
			lower = lowest;
			lowest = array[i];
		}
		else if(array[i] < lower){
			lower = array[i];
		}
	}

	printf("%d and %d\n", lowest, lower);
	
	return 0;
}
