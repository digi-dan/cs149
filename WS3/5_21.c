#include <stdio.h>
#include <string.h>

int main(void) {

	const int MAX_WORDS = 20;
	const int MAX_CHAR = 10;
	char words[MAX_WORDS][MAX_CHAR];
	char searchCharacter;
	int num;
	int i = 0;

	scanf("%d", &num);
	while(i < num){
		scanf("%s", &words[i]);
		i += 1;
	}
	scanf(" %c", &searchCharacter);

	for(i = 0; i < num; i++){
		if(strchr(words[i], searchCharacter) != NULL){
			printf("%s,", words[i]);
		}
	}
	printf("\n");
	return 0;
}
