#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Define your function here */
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]){
int i, j;
for(i = 0, j = 0; userString[i] != '\0' && i < 50; i++){
if(isalpha(userString[i])){
userStringAlphaOnly[j] = userString[i];
j++;
}
}
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
