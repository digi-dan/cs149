/**
* Question 4
 * Author Name: Danny Garcia
 * Author email: danny.garcia@sjsu.edu
 * Last modified Date: 04/24/2023
 * Creation Date: 04/22/2023
 *
 * This program will compile and run like normal.
 * However, this program will have a memory leak because the memory being allocated is never freed
 * You will be able to detect the memory leak with both gdb and valgrind
 *
*/

#include <stdlib.h>

int main(){
    int* ptr = (int*) malloc(sizeof(int));
    *ptr = 100;

    return 0;
}