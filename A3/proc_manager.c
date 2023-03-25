/**
*  Description: This C program executes multiple commands
 *  from each line in stdin and each child process will
 *  write its stdout and stderr to log files
 * Author Name: Danny Garcia
 * Author email: danny.garcia@sjsu.edu
 * Last Modified Date: 03-21-2023
 * Creation Date: 03-20-2023
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_COMMANDS 100
#define COMMAND_LENGTH 30

int main(){
    char command[COMMAND_LENGTH];
    char* arguments[MAX_COMMANDS];
    char outFile[255];  // Output file
    char errorFile[255];    // Error file
    char line[255];
    int index = 1;  // Keep track of number of commands

    int pid;
    int status;

    while(1){
        int numCmd= 0;
        // If CTRL+D is inputted
        if (fgets(command, COMMAND_LENGTH, stdin) == NULL){
            break;
        }

        // Check if the command length has been reached
        if(strlen(command) == COMMAND_LENGTH - 1 && command[COMMAND_LENGTH - 2] != '\n'){
            fprintf(stderr, "Command character length reached\n");
            // Consume any remaining input until a newline is encountered
            int c;
            while((c = getchar()) != '\n' && c != EOF){}
            continue; // Next command
        }
        command[strcspn(command, "\n")] = '\0'; // Remove trailing newline

        arguments[numCmd++] = strtok(command, " \n\t");
        while((arguments[numCmd++] = strtok(NULL, " \n\t")) != NULL){
            if(numCmd == MAX_COMMANDS){
                fprintf(stderr, "Maximum commands reached\n");
                exit(1);
            }
        }
        arguments[numCmd] = NULL;

        // fork child process
        pid = fork();
        if(pid < 0){
            perror("fork");
            exit(1);
        }else if(pid == 0){
            // Child process
            snprintf(outFile, sizeof(outFile), "%d.out", getpid());
            snprintf(errorFile, sizeof (errorFile), "%d.err", getpid());

            int outFd;
            int errFd;

            mode_t mode = S_IRWXU | S_IRWXG | S_IRWXO;

            if((outFd = open(outFile, O_RDWR | O_CREAT | O_APPEND, mode)) < 0){
                perror("open");
                exit(1);
            }
            if((errFd = open(errorFile, O_RDWR | O_CREAT | O_APPEND, mode)) < 0){
                perror("open");
                exit(1);
            }
            // Write to output and error files
            if(dup2(outFd, 1) < 0){
                perror("dup2");
                exit(1);
            }
            if(dup2(errFd, 2) < 0){
                perror("dup2");
                exit(1);
            }
            close(outFd);
            close(errFd);

            snprintf(line, sizeof(line), "Starting command %d: child %d pid of parent %d\n", index, getpid(), getppid());
            int fd;

            if((fd = open(outFile, O_RDWR | O_CREAT | O_APPEND, mode)) < 0){
                perror("open");
                exit(1);
            }

            if(write(fd, line, strlen(line)) < 0){
                perror("write");
                exit(1);
            }

            close(fd);
            if(execvp(arguments[0], arguments) < 0){
                snprintf(line, sizeof(line), "%s: %s\n", arguments[0], strerror(errno));

                if((fd = open(errorFile, O_RDWR | O_CREAT | O_APPEND, mode)) < 0){
                    perror("open");
                    exit(1);
                }

                if(write(fd, line, strlen(line)) < 0){
                    perror("write");
                    exit(1);
                }

                close(fd);
                exit(2);
            }
        }
        else{
            // Parent Process
            wait(&status);  // Wait for child process to finish
            if(WIFEXITED(status)){
                snprintf(outFile, sizeof(outFile), "%d.out", pid);
                snprintf(errorFile, sizeof(errorFile), "%d.err", pid);
                snprintf(line, sizeof(line), "Finished child %d pid of parent %d\n", pid, getpid());

                int fd;
                mode_t mode = S_IRWXU | S_IRWXG | S_IRWXO;
                // Write to output file
                if((fd = open(outFile, O_RDWR | O_CREAT | O_APPEND, mode)) < 0){
                    perror("open");
                    exit(1);
                }
                if(write(fd, line, strlen(line)) < 0){
                    perror("write");
                    exit(1);
                }
                close(fd);

                // Write to error file
                if((fd = open(errorFile, O_RDWR | O_CREAT | O_APPEND, mode)) < 0){
                    perror("open");
                    exit(1);
                }
                snprintf(line, sizeof (line), "Exited with code = 0\n");
                if(write(fd, line, strlen(line)) < 0){
                    perror("write");
                    exit(1);
                }
                close(fd);
            } else if (WIFSIGNALED(status)){
                snprintf(errorFile, sizeof(errorFile), "%d.err", pid);
                snprintf(line, sizeof (line), "Killed with signal 15\n");
                
                int fd;
                mode_t mode = S_IRWXU | S_IRWXG | S_IRWXO;
                if((fd = open(errorFile, O_RDWR | O_CREAT | O_APPEND, mode)) < 0){
                    perror("open");
                    exit(1);
                }

                if(write(fd, line, strlen(line)) < 0){
                    perror("write");
                    exit(1);
                }
                close(fd);
            }
        }
        index++;
    }
    return 0;
}