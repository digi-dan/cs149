#include <stdio.h>
#include <stdbool.h>

/* Define your function here */
bool IsArrayMult10(int inputVals[], int numVals){
	for(int i = 0; i < numVals; i ++){
		if(inputVals[i] % 10 != 0){
			return false;
		}
	}
	
	return true;
}

bool IsArrayNoMult10(int inputVals[], int numVals){
	for(int j = 0; j < numVals; j++){
		if(inputVals[j] % 10 == 0){
			return false;
		}
	}
	
	return true;
}

int main(void) {

	/* Type your code here. Remember to include the bool library*/
	int numVals, inputVals[20];
	bool isMult10, isNoMult10;

	scanf("%d", &numVals);

	for(int k = 0; k < numVals; k++){
		scanf("%d", &inputVals[k]);
	}

	isMult10 = IsArrayMult10(inputVals, numVals);
	isNoMult10 = IsArrayNoMult10(inputVals, numVals);

	if(isMult10){
		printf("all multiples of 10\n");
	}else if(isNoMult10){
		printf("no multiples of 10\n");
	}else{
		printf("mixed values\n");
	}
	
	return 0;
}
