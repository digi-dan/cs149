#include <stdio.h>
#include <string.h>

int main(void) {

	char input[51];

	while(1){

		fgets(input, 51, stdin);

		if(strcmp(input, "Done\n") == 0 || strcmp(input, "done\n") == 0 || strcmp(input, "d\n") == 0){
			break;
		}

		int len = strlen(input);
		
		for(int i = len -2; i >= 0; --i){
			printf("%c", input[i]);
		}
		printf("\n");
	}
	
	return 0;
}
