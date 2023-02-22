/**
 * Description: This program counts the occurrence of each name in a file and outputs the results
 * Author Name: Danny Garcia
 * Author email: danny.garcia@sjsu.edu
 * Last modified date: 02-20-2023
 * Creation Date: 02-16-2023
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("No file specified\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        printf("Error: Unable to open file\n");
        return 1;
    }

    const int MAX_NAMES = 100;
    const int NAME_LENGTH = 30;
    char names[MAX_NAMES][NAME_LENGTH];
    int count[MAX_NAMES];
    int k = 0;
    int empty = 1;

    // Initialize the values in array count to 0
    for(int j = 0; j < MAX_NAMES; j++){
        count[j] = 0;
    }
    /**
     * This function reads in a name, separated by a new line, and puts them in an array while
     *  counting the occurrence of each name in the array
     * Assumptions: There is a text file that is being read with names written in it
     * Inputs: text file with names separated by new lines
     * Returns: two arrays, one with each name at a given index and another array that keeps track
     *  of how many times a name shows up in a text file
     */

    //  Reads the name from the file
    while(fgets(names[k], NAME_LENGTH, file)){

        //  Removes the newline character
        names[k][strcspn(names[k], "\n")] = '\0';

        //Print warning messages to stderr about empty lines
        if(names[k][0] == '\0'){
            fprintf(stderr, "Warning - Line %d is empty\n", k + empty);
            empty++;
        }

        //  Only counts non-empty lines
        if(names[k][0] != '\0'){
            int found = 0;
            for (int i = 0; i < k; i++) {
                if(strcmp(names[i], names[k]) == 0){
                    count[i]++;
                    found = 1;
                }
            }

            //  If the name has not yet been added to the array
            if(found == 0){
                k++;    // Add a new name to the array
            }

        }
    }

    fclose(file);

    if(k == 0){
        printf("No names found in file\n");
        return 0;
    }

    //  Print the results
    printf("Name Count\n");
    for(int i = 0; i < k; i++){
        printf("%s:\t%d\n", names[i], count[i] + 1);
    }

    return 0;
}