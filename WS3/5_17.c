#include <stdio.h>

int main(void) {
	const int NUM_ELEMENTS = 9;
	int userValues[NUM_ELEMENTS];    // Set of data specified by the user
	int input;
	int count = 0;

	while(scanf("%d", &input) == 1){
		if(input < 0){
			break;
		}
		if(count > NUM_ELEMENTS){
			break;
		}

		userValues[count] = input;
		count += 1;
	}

	if(count > NUM_ELEMENTS){
		printf("Too many numbers\n");
	}
	else{
		count /= 2;
		printf("Middle item: %d\n", userValues[count]);
	}

	return 0;
}
