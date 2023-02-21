#include <stdio.h>

int main(void) {
	const int NUM_ELEMENTS = 20;         // Number of input integers
	int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers
	int input;
	int index = -1;

	while(scanf("%d", &input) == 1){
		index += 1;
		userVals[index] = input;
	}
	
	while(index > 0){
		printf("%d,", userVals[index]);
		index -= 1;
	}
	printf("\n");

	return 0;
}
