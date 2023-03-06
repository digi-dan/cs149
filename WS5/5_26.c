#include <stdio.h>
#include <string.h>

int main(void) {
   
   /* Type your code here. */
char input[51];
int count = 0;
int i;

fgets(input, 51, stdin);

for(i = 0; input[i] != '\0' && i < 50; i++){
if(input[i] != ' ' && input[i] != '.' && input[i] != '!' &&input[i] != ',')
count++;
}
printf("%d\n",count);
   return 0;
}
