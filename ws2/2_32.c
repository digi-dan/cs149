/*
	CS 149
	Danny Garcia
	2.32 zyBooks Lab
	Input and formatted output: House real estate summary
*/
#include <stdio.h>

int main(void) {
   int currentPrice;
   int lastMonthsPrice;
   
   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);

	printf("This house is $%d. The change is $%d since last month.\n", currentPrice, currentPrice - lastMonthsPrice);
	printf("The estimated monthly mortgage is $%lf.\n", (double)(currentPrice * 0.051) / 12);
   return 0;
}
