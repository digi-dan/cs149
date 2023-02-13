/* CS 149
	Danny Garcia
	2.25 zyBooks Lab
	Divide by x
*/
#include <stdio.h>

	int main(void) {

	int userNum;
	int x;

	scanf("%d", &userNum);
	scanf("%d", &x);

	userNum /= x;
	printf("%d ", userNum);

	userNum /= x;
	printf("%d ", userNum);

	userNum /= x;
	printf("%d\n", userNum);

   return 0;
}
