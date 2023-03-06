/**
*	Description: Counts the input length of a string
*	excluding spaces, periods, exclamation marks, and commas
*	Input String shall not exceed 50 characters
*	Creation Date: 03/05/2023
*	Last Modified Date: 03/05/2023
**/
#include <stdio.h>
#include <string.h>

int main(void) {
   
	/* Type your code here. */
	char input[51];
	int count = 0;
	int i;

	fgets(input, 51, stdin);
	/* Counts the number of characters excluding spaces, periods, exclamation marks, and 	commas*/
	for(i = 0; input[i] != '\0' && i < 50; i++){
		if(input[i] != ' ' && input[i] != '.' && input[i] != '!' &&input[i] != ',')
			count++;
	}
	printf("%d\n",count);
	return 0;
}
