#include <stdio.h>
#include <string.h>

typedef struct ContactNode_struct {
	/* Define ContactNode struct here. */
	char contactName[100];
	char contactPhoneNumber[100];
	struct ContactNode* nextNodePtr;

}ContactNode;

/* Define the functions here. */
void InitializeContactNode(ContactNode* thisNode, char name[], char phone[]){
	strcpy(thisNode->contactName, name);
	strcpy(thisNode->contactPhoneNumber, phone);
	thisNode->nextNodePtr = NULL;
}

char* GetName(ContactNode* thisNode){
	return thisNode->contactName;
}

char* GetPhoneNumber(ContactNode* thisNode){
	return thisNode->contactPhoneNumber;
}

void InsertAfter(ContactNode* thisNode, ContactNode* newNode){
	ContactNode* tmpNext = NULL;
	tmpNext = thisNode->nextNodePtr;
	thisNode->nextNodePtr = newNode;
	newNode->nextNodePtr = tmpNext;
}

ContactNode* GetNext(ContactNode* thisNode){
	return thisNode->nextNodePtr;
}

void PrintContactNode(ContactNode* thisNode){
	printf("Name: %s\nPhone number: %s\n", thisNode->contactName, thisNode->contactPhoneNumber);
}

int main(void) {
	/* Type your code here. */
	ContactNode contact1, contact2, contact3, *currNodePtr = NULL;

	InitializeContactNode(&contact1, "","");
	InitializeContactNode(&contact2, "","");
	InitializeContactNode(&contact3, "","");

	scanf("%[^\n]%*c", contact1.contactName);
	scanf("%[^\n]%*c", contact1.contactPhoneNumber);
	scanf("%[^\n]%*c", contact2.contactName);
	scanf("%[^\n]%*c", contact2.contactPhoneNumber);
	scanf("%[^\n]%*c", contact3.contactName);
	scanf("%[^\n]%*c", contact3.contactPhoneNumber);

	printf("Person 1: %s, %s\n", contact1.contactName, contact1.contactPhoneNumber);
	printf("Person 2: %s, %s\n", contact2.contactName, contact2.contactPhoneNumber);
	printf("Person 3: %s, %s\n", contact3.contactName, contact3.contactPhoneNumber);

	currNodePtr = &contact1;
	InsertAfter(currNodePtr, &contact2);
	currNodePtr = &contact2;
	InsertAfter(currNodePtr, &contact3);
	currNodePtr = &contact1;

	printf("\nCONTACT LIST\n");
	while(currNodePtr != NULL){
		PrintContactNode(currNodePtr);
		printf("\n");
		currNodePtr = GetNext(currNodePtr);
	}

	return 0;
}
