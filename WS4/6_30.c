/**
*	Description: Reads in 4 integers and returns the
*	biggest integer and the smallest integer
*	Author Name: Danny Garcia
*	Author email: danny.garcia@sjsu.edu
*	Last Modified Date: 02/27/2023
**/
#include <stdio.h>

/*Function that takes in 4 integers and returns the largest integer*/
int MaxNumber(int num1, int num2, int num3, int num4){
	
	// intialize variable max to first integer
	int max = num1;
	
	// Compare max with rest of input
	if(num2 > max){
		max = num2;
	}
	if(num3 > max){
		max = num3;
	}
	if(num4 > max){
		max = num4;
	}
	
	// Return maximum number
	return max;
}

/*Functio that takes in 4 inegers and returns the smallest integer*/
int MinNumber(int num1, int num2, int num3, int num4){
	
	// Initalize variable min to first inputted integer
	int min = num1;
	
	// Compare min with rest of input
	if(num2 < min){
		min = num2;
	}
	if(num3 < min){
		min = num3;
	}
	if(num4 < min){
		min = num4;
	}
	
	// Return minimum number
	return min;
}
int main(void) {
	
	// Initialize input variables and scan for input
	int num1, num2, num3, num4;
	scanf("%d%d%d%d", &num1, &num2, &num3, &num4);
	
	// Call and print the Min and Max function
	printf("Maximum is %d\n", MaxNumber(num1, num2, num3, num4));
	printf("Minimum is %d\n", MinNumber(num1, num2, num3, num4));

	return 0;
}
