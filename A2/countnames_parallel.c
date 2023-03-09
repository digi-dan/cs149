/**
 *  Description: This program counts the occurrence of each name in multiple
 *  files inputted from the command line and outputs the results of each name
 *  Author Name: Danny Garcia
 *  Author email: danny.garcia@sjsu.edu
 *  Last modified date: 03/06/2023
 *  Creation Date: 03/04/2023
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_NAMES 100
#define NAME_LENGTH 30

int main(int argc, char *argv[]) {

    // No File inputted
    if (argv[1] == NULL) {
        return 0;
    }

    // Data Structure for the total occurrences for names across all files
    struct names {
        char name[NAME_LENGTH];
        int count;
    };

    struct names allNames[MAX_NAMES];

    // Initialize the pipes for parent and child to communicate
    int fd[2];
    // Parent to child pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    int fd1[2];
    // Child to parent pipe
    if (pipe(fd1) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Child Process
    pid_t pid;

    for (int i = 1; i < argc; ++i) {
        write(fd[1], argv[i], MAX_NAMES);
        // Fork child
        pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Pipe failed");
            return 1;
        } else if (pid == 0) {    // Child Process

            close(fd1[0]);  // Close reading for child to parent
            close(fd[1]);   // Close writing for parent to child
            // Prevents child to continue forking children
            break;
        }
    }

    // Parent process
    if (pid > 0) {
        close(fd[0]);   // Close reading for parent to child
        close(fd1[1]);  // Close writing for child to parent
        // Wait for child to finish
        wait(NULL);

        // Initialize data structure to store pipe names
        struct names pipeNames;
        int total = 0;
        int namesRead = sizeof(pipeNames);

        while ((namesRead = read(fd1[0], &pipeNames, sizeof(pipeNames))) == sizeof(pipeNames)) {
            int match = 1;

            // Check if any of the same names occurred in other files
            for (int i = 0; i < total; ++i) {
                // If same name add to total count
                if (strcmp(pipeNames.name, allNames[i].name) == 0) {
                    allNames[i].count += pipeNames.count;
                    match = 0;
                }

                if (!match) {
                    break;
                }
            }
            // If no match was found, add new name to array with the correct count
            if (match) {
                strcpy(allNames[total].name, pipeNames.name);
                allNames[total].count = pipeNames.count;
                // Increment total index
                total++;
            }
        }

        // Print results, this will happen once parent is done
        for(int j = 0; j < total; ++j) {
            printf("%s: %d\n", allNames[j].name, allNames[j].count);
        }

        return 0;
    }
    /*
     *  This function is an extension of A1. Given an inputted file,
     *  this function will count the number of times a name shows up in the file
     *  and return the number of times each name is in the file
     */
    char fileName[MAX_NAMES];
    read(fd[0], fileName, MAX_NAMES);
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        fprintf(stderr, "range: cannot open file\n");
        return 1;
    }
    int k = 0;
    char input[NAME_LENGTH];
    int emptyLine = 0;
    
    while(fgets(input, NAME_LENGTH, file)){

        ++emptyLine;
        // If empty line, print warning
        if(isspace(input[0])){
            fprintf(stderr, "Warning - Line %d is empty in file: %s\n", emptyLine, fileName);
            continue;
        }
        // Remove the newline character
        input[strcspn(input, "\n")] = '\0';

        int found = 1;

        // Iterate through the list
        for(int m = 0; m < k; ++m) {
            // If same name is found, add to count
            if (strcmp(input, allNames[m].name) == 0) {
                allNames[m].count++;
                found = 0;
            }
            if (!found) {
                break;
            }
        }
        // Add new name to the data structure
        if(found){
            strcpy(allNames[k].name, input);
            allNames[k].count = 0;
            allNames[k].count++;
            k++;
        }

    }
    // Write name to parent
    for(int n = 0; n < k; ++n){
        write(fd1[1], &allNames[n], sizeof(allNames[n]));
    }
    // Close file
    fclose(file);
    exit(0);
}

