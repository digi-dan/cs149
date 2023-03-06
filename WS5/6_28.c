/**
*	Description: Given a string of up to 50 characters, this program will
*	print out the given string after removing all non-alphabetic characters
*	Creation Date: 03/05/2023
*	Last Modified Date: 03/05/2023
*	Email: danny.garcia@sjsu.edu
**/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Define your function here */
// Function will move all alphabetic characters from userString to userStringAlphaOnly
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]){
	int i, j;
	// Iterate through userString array
	for(i = 0, j = 0; userString[i] != '\0' && i < 50; i++){
		// If character is alphabetic, add to userStringAlphaOnly
		if(isalpha(userString[i])){
			userStringAlphaOnly[j] = userString[i];
			j++;
		}
	}
	// Append String with null character
	userStringAlphaOnly[j] = '\0';
}

int main(void) {

	/* Type your code here. */
	char userString[51];
	char userStringAlphaOnly[51];

	fgets(userString, 51, stdin);

	RemoveNonAlpha(userString, userStringAlphaOnly);
	printf("%s\n", userStringAlphaOnly);

	return 0;
}
