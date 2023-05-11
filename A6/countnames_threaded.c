#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

/*****************************************
//CS149 SP23
//Template for assignment 6
//San Jose State University
//originally prepared by Bill Andreopoulos
*****************************************/

//thread mutex lock for access to the log index
//TODO you need to use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for critical sections of allocating THREADDATA
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

//thread mutex lock for access to the name counts data structure
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT
{
    pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p=NULL;
//variable for indexing of messages by the logging function.
int logindex=0;
int *logip = &logindex;

//The name counts.
// You can use any data structure you like, here are 2 proposals: a linked list OR an array (up to 100 names).
//The linked list will be faster since you only need to lock one node, while for the array you need to lock the whole array.
//You can use a linked list template from A5. You should also consider using a hash table, like in A5 (even faster).
struct NAME_NODE{
    char* name;
    int count;
    struct node *next;
    pthread_mutex_t lock;
};

static struct NAME_NODE *hashTable[101];

unsigned hash(char* name){
    unsigned hashValue;
    for (int hashValue = 0; *name != '\0'; name++) {
        hashValue = *name + 31 * hashValue;
    }

    return hashValue * 101;
}

struct NAME_NODE *find(char* name){
    struct NAME_NODE *temp;
    for(temp = hashTable[hash(name)]; temp != NULL; temp = temp->next){
        if(strcmp(name, temp->name) == 0){
            return temp;
        }
    }

    return NULL;
}

struct NAME_NODE *addNode(char* name){
    struct NAME_NODE *temp = NULL;
    unsigned hashValue;

    pthread_mutex_lock(&tlock3);
    if((temp = find(name)) == NULL){
        temp = (struct NAME_NODE*) malloc(sizeof(struct NAME_NODE));

        if(temp == NULL){
            return NULL;
        }

        temp->name = strdup(name);
        temp->count = 1;
        pthread_mutex_init(&(temp->lock), NULL);
        hashValue = hash(name);
        temp->next = hashTable[hashValue];
        hashTable[hashValue] = temp;
    }else{
        pthread_mutex_lock(&(temp->lock));
        temp->count++;
        pthread_mutex_unlock(&(temp->lock));
    }
    pthread_mutex_unlock(&tlock3);

    return temp;
}

struct NAME_NODE* insert(char* name){
    struct NAME_NODE* temp = NULL;
    temp = find(name);

    if(temp != NULL){
        pthread_mutex_lock(&(temp->lock));
        temp->count++;
        pthread_mutex_unlock(&(temp->lock));
        return temp;
    }
    return addNode(name);
}

void logprint(char* message){

    int hour;
    int minute;
    int second;
    int day;
    int month;
    int year;

    time_t timeNow;
    time(&timeNow);

    struct tm* local = localtime(&timeNow);
    hour = local->tm_hour;
    minute = local->tm_min;
    second = local->tm_sec;
    day = local ->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    pthread_mutex_lock(&tlock1);
    if(hour < 12) {
        fprintf(stdout, "Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d am: %s\n", ++logindex,
                pthread_self(), getpid(), day, month, year, hour, minute, second, message);
    } else{
        fprintf(stdout, "Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d pm: %s\n", ++logindex, pthread_self(), getpid(), day, month, year, hour - 12, minute, second, message);
    }
    pthread_mutex_unlock(&tlock1);
}

/*********************************************************
// function main
*********************************************************/
int main(int argc, char* argv[])
{
    //TODO similar interface as A2: give as command-line arguments three filenames of numbers (the numbers in the files are newline-separated).

    if(argc != 3){
        fprintf(stderr, "Error: Please provide 2 files\n");
        pthread_exit(NULL);
    }

    printf("======================== Log Messages ========================\n");
    printf("create first thread\n");
    pthread_create(&tid1,NULL,thread_runner,argv[1]);

    printf("create second thread\n");
    pthread_create(&tid2,NULL,thread_runner,argv[2]);

    printf("wait for first thread to exit\n");
    pthread_join(tid1,NULL);
    printf("first thread exited\n");

    printf("wait for second thread to exit\n");
    pthread_join(tid2,NULL);
    printf("second thread exited\n");

    //TODO print out the sum variable with the sum of all the numbers

    printf("======================== Name Counts ========================\n");
    for(int i = 0; i < 101; i++){
        struct NAME_NODE* current = hashTable[i];
        while(current != NULL){
            fprintf(stdout, "%s. %d\n", current->name, current->count);
            current = current->next;
        }

        struct NAME_NODE* temp = hashTable[i];
        while (temp != NULL){
            struct NAME_NODE* temp1 = temp->next;
            free(temp->name);
            free(temp);
            temp = temp1;
        }

        hashTable[i] = NULL;
    }
    exit(0);

}//end main

/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void* thread_runner(void* x)
{
    char* fileName = (char*) x;
    char message[100];

    pthread_t me;

    me = pthread_self();
    sprintf(message,"This is thread %ld (p=%p)",me,p);
    logprint(message);

    pthread_mutex_lock(&tlock2); // critical section starts
    if (p==NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
        p->creator=me;
    }
    if (p!=NULL && p->creator==me) {
        sprintf(message,"This is thread %ld and I created THREADDATA %p",me,p);
        logprint(message);
    } else {
        sprintf(message,"This is thread %ld and I can access the THREADDATA %p",me,p);
        logprint(message);
    }
    pthread_mutex_unlock(&tlock2); // critical section ends

    /**
    * //TODO implement any thread name counting functionality you need.
    * Assign one file per thread. Hint: you can either pass each argv filename as a thread_runner argument from main.
    * Or use the logindex to index argv, since every thread will increment the logindex anyway
    * when it opens a file to print a log message (e.g. logindex could also index argv)....
    * //Make sure to use any mutex locks appropriately
    */
    // TODO use mutex to make this a start of a critical section
    // critical section starts
    FILE* file = fopen(fileName, "r");
    logprint(message);

    if(!file){
        logprint(message);
        pthread_exit(NULL);
    }

    int i = 0;

    while (true){
        i++;

        char *input = NULL;
        size_t length;

        if(getline(&input, &length, file) == -1){
            free(input);
            break;
        }

        if(input[0] == '\n' || (input[0] == ' ' && (input[1] == '\n' || input[1] == '\0'))) {
            fprintf(stderr, "Warning - file %s line %d is empty.\n", file, i);
            free(input);
            continue;
        }

        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        while(insert(input) == NULL){

        }
        free(input);
    }

    if(ferror(file)){
        pthread_exit(NULL);
    }
    fclose(file);

    pthread_mutex_lock(&tlock2);

    if (p!=NULL && p->creator==me) {
        sprintf(message,"This is thread %ld and I delete THREADDATA %p",me, p);
        logprint(message);
        free(p);
        p = NULL;
    /**
    * TODO Free the THREADATA object.
    * Freeing should be done by the same thread that created it.
    * See how the THREADDATA was created for an example of how this is done.
    */
    } else {
        sprintf(message,"This is thread %ld and I can access the THREADDATA %p",me, p);
        logprint(message);
    }

    // TODO critical section ends
    pthread_mutex_unlock(&tlock2);
    pthread_exit(NULL);
    //return NULL;
}//end thread_runner