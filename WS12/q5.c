/**
 * Question 5
 * Author Name: Danny Garcia
 * Author email: danny.garcia@sjsu.edu
 * Last modified Date: 04/24/2023
 * Creation Date: 04/22/2023
 *
 * The program compiles and runs like normal.
 * When running this program through valgrind, we get an error
 * for a memory leak.
 * The program is incorrect
 */

#include <stdlib.h>

int main(){

    int* data = (int*) malloc(sizeof(int));
    data[100] = 0;

    return 0;
}