#include <stdio.h>

int main(void) {

	int input;
	int max = 0;
	double average = 0.0;
	int count = 0;

	while(scanf("%d", &input) == 1){
		if(input < 0){
			break;
		}
		average += input;
		count += 1;

		if(input > max){
			max = input;
		}

	};

	average /= count;

	printf("%d ", max);
	printf("%.02lf\n", average);

	return 0;
}
