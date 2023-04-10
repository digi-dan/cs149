#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {

	/* Type your code here */  
	ItemToPurchase item1, item2;
	char c;

	printf("Item 1\n");
	printf("Enter the item name:\n");
	scanf("%[^\n]%*c", item1.itemName);
	printf("Enter the item price:\n");
	scanf("%d", &item1.itemPrice);
	printf("Enter the item quantity:\n");
	scanf("%d", &item1.itemQuantity);
	printf("\n");

	printf("Item 2\n");
	printf("Enter the item name:\n");
	c = getchar();
	
	while(c != '\n' && c != EOF){
		c = getchar();
	}
	scanf("%[^\n]%*c", item2.itemName);
	printf("Enter the item price:\n");
	scanf("%d", &item2.itemPrice);
	printf("Enter the item quantity:\n");
	scanf("%d", &item2.itemQuantity);
	printf("\n");

	printf("TOTAL COST\n");
	PrintItemCost(item1);
	PrintItemCost(item2);
	printf("\n");
	printf("Total: $%d\n", item1.itemPrice *item1.itemQuantity + item2.itemPrice * item2.itemQuantity);

	return 0;
}
