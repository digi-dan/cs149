#include<stdio.h>
#include <string.h>

int main(void) {

	/* Type your code here. */
	char inputString[100];
	char quitChar = 'q';

	while(1){
		char firstWord[50] = {'\0'};
		char secondWord[50] = {'\0'};
		printf("Enter input string:\n");
		fgets(inputString, 100, stdin);

		if(inputString[0] == quitChar){
			break;
		}

		if(strchr(inputString, ',') == NULL){
			printf("Error: No comma in string.\n\n");
			continue;
		}

		int i, j;
		int k = 0;

		for(i = 0; inputString[i] != '\0'; i++){
			if(inputString[i] == ' '){
				continue;
			}
			if(inputString[i] == ','){
			
				firstWord[i] = '\0';
				i++;
				for(j = i; inputString[j] != '\0'; j++){
					if(inputString[j] == ' '){
						continue;
					}
					
					secondWord[k] = inputString[j];
					k++;
				}
				secondWord[k] = '\0';
			}
			firstWord[i] = inputString[i];
		}

		printf("First word: %s\n", firstWord);
		printf("Second word: %s\n", secondWord);
	}

	return 0;
}
