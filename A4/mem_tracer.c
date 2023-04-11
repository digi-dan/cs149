/**
 * Description: Stores command lines in an array and traces the memory usage
 * Reads all lines from stdin into a dynamically allocated array of type char **
 * Author name: Danny Garcia
 * Author email: danny.garcia@sjsu.edu
 * Last Modified Date: 04/10/2023
 * Creation Date: 04/06/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/**
 *  TRACE_NODE_STRUCT is a linked list of pointer to function identifiers
 *  TRACE_TOP is the head of the list is the top of the stack
 */
struct TRACE_NODE_STRUCT{
    char* line;   // ptr to function identifier (a function name)
    int index;
    struct TRACE_NODE_STRUCT* next; // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE *TRACE_TOP = NULL;    // ptr to the top of the stack

// Recursive function that prints the contents of all nodes in the linked list
void PrintNodes(TRACE_NODE *head){
    if(head == NULL){
        return;
    }

    printf("Index: %d; Line: %s\n", head ->index, head->line);
    PrintNodes(head->next);
}

/**
*  function PUSH_TRACE
 *  The purpose of this stack is to trace the sequence of function calls,
 *  just like the stack in your computer would do.
 *  The "global" string denotes the start of the function call trace.
 *  The char *p parameter is the name of the new function that is added to the call trace.
*/
void PUSH_TRACE(char* p) {   // push p on the stack
    TRACE_NODE* tnode;
    static char glob[] = "global";

    if (TRACE_TOP == NULL) {

        // initialize the stack with "global" identifier
        TRACE_TOP = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

        // no recovery needed if allocation failed, this is only used in debugging,
        // not in production
        if(TRACE_TOP == NULL) {
            printf("PUSH_TRACE: memory allocation error\n");
            exit(1);
        }

        TRACE_TOP->line = glob;
        TRACE_TOP->next = NULL;
    }   // if

    // create node for p
    tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only used in debugging,
    // not in production
    if(tnode == NULL){
        printf("PUSH_TRACE: memory allocation error\n");
        exit(1);
    }   // if
    tnode->line = p;
    tnode->next = TRACE_TOP;    // insert fnode as the first in the list
    TRACE_TOP = tnode;  // point TRACE_TOP to the first node

}/* end PUSH_TRACE*/

/**
*  function POP_TRACE
*  Pop a function call from the stack
*/
void POP_TRACE(){   // remove the op of the stacke
    TRACE_NODE* tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);
}/* end POP_TRACE*/

/**
 * function PRINT_TRACE
 * prints out the sequence of function calls that are on the stack at this instance
 * For example, it returns a string that looks like: global:funcA:funcB:funcC.
 * Printing the function call sequence the other way around is also ok:
 * funcC:funcB:funcA:global
*/
char *PRINT_TRACE(){
    int depth = 50; // A max of 50 levels in the stack will be combined in a string for printing out
    int i, length, j;
    TRACE_NODE *tnode;
    static char buf[100];

    if(TRACE_TOP == NULL){  // stack not initialized yet, so we are still in the 'global' area
        strcpy(buf, "global");
        return buf;
    }

    /* peek at the depth(50) top entries on the stack, but do not go over 100 chars
     * and do not go over the bottom of the stack */
    sprintf(buf, "%s", TRACE_TOP->line);
    length = strlen(buf);   // length of the string so far
    for(i = 1, tnode = TRACE_TOP->next; tnode != NULL && i < depth; i++, tnode = tnode->next) {
        j = strlen(tnode->line);    // length of what we want to add
        if (length + j + 1 < 100) {   // total length is ok
            sprintf(buf + length, ":%s", tnode->line);
            length += j + 1;
        } else  // it would be too long
            break;
    }
    return buf;
}   /* end PRINT_TRACE */

/**
 * function REALLOC
 * calls realloc. Prints info about memory usage
 * Information about the function F should be printed by printing the stack (use PRINT_TRACE)
*/
void* REALLOC(void* p, int t, char* file, int line){
    p = realloc(p, t);
    if(p == NULL){
        fprintf(stderr, "Realloc failed for line %d.\n", line);
        exit(-1);
    }
    FILE* fp = fopen("memtrace.out", "a");
    fprintf(fp, "File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file , line, PRINT_TRACE(), p, t);
    return p;
}

/**
 * function MALLOC
 * calls malloc. Prints info about memory usage
*/
void* MALLOC(int t, char* file, int line){
    void* p;
    p = malloc(t);
    FILE* fp = fopen("memtrace.out", "a");
    fprintf(fp, "File %s, line %d, function %s allocated new memory segment at address %p to size %d\n", file, line, PRINT_TRACE(),p, t);
    return p;
}

/**
 * function FREE
 * calls free
*/
void FREE(void* p, char* file, int line){
    FILE* fp = fopen("memtrace.out", "a");
    fprintf(fp, "File %s, line %d, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(),p);
    free(p);
}
#define realloc(a,b) REALLOC(a, b, __FILE__, __LINE__)
#define malloc(a) MALLOC(a, __FILE__, __LINE__)
#define free(a) FREE(a, __FILE__, __LINE__)

/**
 * function add_column
 * will add an extra column to a 2d array of ints
 * This function is intended to demonstrate how memory usage tracing of realloc is done
 * Returns the number of new columns (updated)
*/
int add_column(int** array, int rows, int columns){
    PUSH_TRACE("add_column");
    int i;

    for(i = 0; i < rows; i++){
        array[i] = (int*) realloc(array[i], sizeof(int)*(columns+1));
        array[i][columns] = 10*i+columns;
    }   // for
    POP_TRACE();
    return (columns+1);
}   // end add_column

/**
* function make_extend_array
 * This function is intended to demonstrate how memory usage tracing of malloc and free is done
*/
void make_extend_array(){
    PUSH_TRACE("make_extend_array");
    int i, j;
    int **array;
    int ROW = 4;
    int COL = 3;

    // make array
    array = (int**)malloc(sizeof(int*)*4); // 4 rows
    for(i = 0; i < ROW; i++){
        array[i] = (int*) malloc(sizeof(int)*3);    // 3 columns
        for(j = 0; j < COL; j++)
            array[i][j] = 10 * i +j;
    }   // for

    // display array
    for(i = 0; i < ROW; i ++)
        for(j = 0; j < COL; j++)
            printf("array[%d][%d] = %d\n", i, j, array[i][j]);
    // and a new column
    int NEWCOL = add_column(array, ROW, COL);

    // now display the array again
    for(i = 0; i < ROW; i++)
        for(j = 0; j < NEWCOL; j++)
            printf("array[%d][%d] = %d\n", i, j, array[i][j]);
    // now deallocate it
    for(i = 0; i < ROW; i++)
        free((void*)array[i]);
    free((void*)array);

    POP_TRACE();
    return;
}   // end make_extend_array

// function main
int main(){
    PUSH_TRACE("main");

    make_extend_array();

    POP_TRACE();
    return(0);
}   // end main