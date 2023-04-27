/**
 * Assignment 5
 * Author Name: Danny Garcia
 * Author email: danny.garcia@sjsu.edu
 * Last modified date: 04/25/2023
 * Creation date: 04/19/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

struct nlist {  /* table entry: */
    struct nlist *next; /* next entry in chain */
    time_t starttime;
    time_t finishtime;
    int index; // this is the line index in the input text file
    int pid; // the process id. you can use the pid result of wait to look up in the hashtable
    char *command; // command. This is good to store for when you decide to restart a command
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* This is the hash function: form hash value for string s */
/* You can use a simple hash function: pid % HASHSIZE */
unsigned hash(int pid){
    unsigned hashval = pid % HASHSIZE;
    return hashval;
}

/* lookup: look for s in the hashtab */
/* TODO change to lookup by pid: struct nlist *lookup (int pid) */
/* TODO modify to search by pid, you won't need strcmp anymore */
/* This is traversing the linked list under a slot of the hash table. The array position to look
 * in is returned by the hash function */
struct nlist *lookup(int pid){
    struct nlist *np;
    for(np = hashtab[hash(pid)]; np != NULL; np = np->next)
        if(pid == np->pid)
            return np;  /* found */
    return NULL;    /* not found */
}

/* insert: put (name, defn) in hashtab */
/* TODO: change this to insert in hash table the info for a new pid and its command */
/* TODO: change signature to: struct nlist *insert(char *command, int pid, int index). */
/* This insert returns a nlist node. Thus when you call insert in your main function
 * you will save the returned nlsit node in a variable (mynode). Then you can set the starttime
 * and finishtime from your main function: mynode->starttime = starttime;
 * mynode->finishtime = finishtime;
 */
struct nlist *insert(char *command, int pid, int index){
    struct nlist *np;
    unsigned hashval;
    //TODO change to lookup by pid. There are 2 cases:
    /* case 1: the pio is not found, you have to create it with
    * malloc. Then you want to set the pio, command and index */
    if((np = lookup(pid)) == NULL){
    np = (struct nlist *) malloc(sizeof(*np));
    if(np == NULL)
        return NULL;
    np->pid = pid;
    np->index = index;
    hashval = hash(pid);
    if((np->command = strdup(command)) == NULL)
        return NULL;
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
    }
    return np;
}

int main(int argc, char* argv[]){
    int count = 0;
    int lines = 10;
    int pid;
    char** commands = (char**)malloc(sizeof(char*) * lines);
    char fileName[31];

    memset(hashtab, 0, 31 * sizeof(struct nlist*));
    memset(commands, 0, sizeof(char*) * lines);

    while(1){
        if(count >= lines){
            lines += 10;
            commands = (char**) realloc(commands, sizeof(char*) * lines);
        }
        char* input = (char*) malloc(sizeof(char) * 31);
        memset(input, 0, 31 * sizeof(char ));

        if(fgets(input, 31, stdin) == NULL){
            free(input);
            break;
        }

        if(input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';

        commands[count] = input;
        count++;
    }

    int i = 0;
    while(i < count){
        time_t starttime = time(NULL);
        pid = fork();
        if(pid < 0){
            return 1;
        }
        else if(pid == 0)
            break;
        else{
            struct nlist* node = insert(commands[i], pid, i);
            node->command = commands[i];
            node->index = ++i;
            node->starttime = starttime;
        }
    }

    if(pid > 0){
        int pid;
        int status;
        while ((pid = wait(&status)) > 0){
            time_t finishtime = time(NULL);
            struct nlist* node1 = lookup(pid);
            node1->finishtime = finishtime;

            sprintf(fileName, "%d.out", pid);
            FILE* fdout = fopen(fileName,"a");
            sprintf(fileName, "%d.err", pid);
            FILE* fderr = fopen(fileName, "a");

            if(WIFEXITED(status)){
                fprintf(fderr, "Exited with exitcode = %d\n", WIFEXITED(status));
            }else if(WIFEXITED(status)){
                fprintf(fderr,"Killed with signal %d\n", WTERMSIG(status));
            }

            fprintf(fderr, "spawning too fast\n");
            fprintf(fdout, "Finished child %d pid of parent %d\n", pid, getpid());
            fprintf(fdout, "Finished at %ld, runtime duration %ld\n", node1->finishtime, node1->finishtime-node1->starttime);
            fclose(fderr);
            fclose(fdout);

            if(node1->finishtime - node1->starttime > 2){
                time_t starttime = time(NULL);
                int pid1 = fork();
                if(pid1 < 0)
                    return 1;
                if(pid1 == 0)
            }
        }
    }
}