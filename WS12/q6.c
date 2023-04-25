/**
* Question 6
 * Author Name: Danny Garcia
 * Author email: danny.garcia@sjsu.edu
 * Last modified Date: 04/24/2023
 * Creation Date: 04/22/2023
 *
 * This program compiles and runs like normal.
 * When using valgrind, there is no error when it comes to memory leaks,
 * however there is an error when printing the value. Since the value
 * being printed is freed, the print statement will print a random value
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int* data = (int*) malloc(sizeof(int));
    data[100] = 0;
    free(data);
    printf("%d\n", data[100]);

    return 0;
}