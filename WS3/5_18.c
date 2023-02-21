#include <stdio.h>

int main(void) {
	const int NUM_ELEMENTS = 20;
	int userValues[NUM_ELEMENTS];    // Set of data specified by the user
	int num;
	int threshold;
	int iter = 0;

	scanf("%d", &num);
	while(scanf("%d", &threshold) == 1){
		if(iter >= num){
			break;
		}
		
		userValues[iter] = threshold;
		iter += 1;
	}
	
	for(iter = 0; iter < num; iter ++){
		if(userValues[iter] <= threshold){
			printf("%d,", userValues[iter]);
		}
	}
	
	printf("\n");

	return 0;
}
