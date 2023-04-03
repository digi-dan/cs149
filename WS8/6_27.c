#include <stdio.h>
#include <string.h>

/* Define your function here */
int CalcNumCharacters(char* userString, char userChar){
	int count = 0;
	for(int i = 0; userString[i] != '\0'; i++){
		if(userString[i] == userChar){
			count++;
		}
	}
	return count;
}

int main(void) {
	/* Type your code here. */
	char userChar, userString[50];
	int count;

	scanf("%c %s", &userChar, userString);

	count = CalcNumCharacters(userString, userChar);

	if(count == 1){
		printf("1 %c\n", userChar);
	}else{
		printf("%d %c's\n", count, userChar);
	}

	return 0;
}
