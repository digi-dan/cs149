#include <stdio.h>

/* Define your function here */ 
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4){
	int temp1 = *userVal1;
	*userVal1 = *userVal2;
	*userVal2 = temp1;

	int temp2 = *userVal3;
	*userVal3 = *userVal4;
	*userVal4 = temp2;
}

int main(void) {

   /* Type your code here. Your code must call the function.  */
	int val1, val2, val3, val4;
	scanf("%d %d %d %d", &val1, &val2, &val3, &val4);

	SwapValues(&val1, &val2, &val3, &val4);

	printf("%d %d %d %d\n", val1, val2, val3, val4);

	return 0;
}
