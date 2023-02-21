#include <stdio.h>

int main(void) {

	const int MAX_INT = 20;
	int num;
	int upper;
	int lower;
	int array[MAX_INT];
	scanf("%d", &num);

	for(int i = 0; i < num; i++){
		scanf("%d", &array[i]);
	}
	scanf("%d", &lower);
	scanf("%d", &upper);

	for(int i = 0; i < num; i++){
		if(array[i] >= lower && array[i] <= upper){
			printf("%d,", array[i]);
		}
	}
	printf("\n");

	return 0;
}
