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
#include <sys/wait.h>

#define NAME_LENGTH 30
#define MAX_NAMES 100

int main(int argc, char *argv[]){
    if(argc == 0){  // No file or names specified
        return 0;
    }

    for(int i = 1; i < argc; i++){
        pid_t pid = fork();

        if(pid == -1){
            fprintf(stderr, "Failed to fork process for %s\n", argv[i]);
            return 1;
        } else if(pid == 0){
            // Child process
            FILE *fp = fopen(argv[i], "r");

            if(!fp){
                fprintf(stderr, "range: cannot open file");
                return 1;
            }
            int counts[MAX_NAMES] = {0};    // Initialize all counts to 0
            char names[MAX_NAMES][NAME_LENGTH +1];

            char line[NAME_LENGTH + 2]; // Max name length +newline + null terminator

            while(fgets(line, sizeof(line), fp)){
                if(line[0] == '\n'){
                    // Skip empty lines
                    continue;
                }

                char *name = strtok(line, "\n");
                int match = 0;

                for(int j = 0; j < MAX_NAMES; j++){
                    if(strcmp(names[j], name) == 0){
                        counts[j]++;
                        match = 1;
                        break;
                    } else if(counts[j] == 0){
                        // Add new name
                        strcpy(names[j], name);
                        counts[j]++;
                        match = 1;
                        break;
                    }
                }

                if(!match){
                    // Max names reached
                    break;
                }
            }

            fclose(fp);

            for(int j = 0; j < MAX_NAMES; j++){
                if(counts[j] > 0){
                    printf("%s: %d\n", names[j], counts[j]);
                }
            }

            return 0;
        }
    }

    // Parent process
    int status;

    // Wait for all child process to finish
    while(wait(&status) > 0);
}