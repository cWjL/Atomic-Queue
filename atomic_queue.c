/*
*
*	Author:				Jacob Loden
*
*	Description:		Program to test semaphore atomicity in multi-threaded execution.
*
*						Program accepts command line integer parameter and runs the number
*						of threads corresponding to this parameter.
*
*						Program first starts parent thread, followed by N child threads.
*						Parent waits for children to finish execution, then prints contents
*						of global array of child threads.  Child threads increment the ith
*						array elements and returns.
*
*						Program will run until user enters <CTRL+C>
*
*
*/
#include <unistd.h>
#include "sem.h"
// Forward function declarations
void print_arr(int);
void parent();
void child();
// Global function pointers
void (*parent_ptr)();
void (*child_ptr)();
// Global variables
Semaphore *parent_mutex, *child_mutex;
int *arr, N;

// Child thread. Runs forever.
void child(){
    while(1) {
        // atomize the child
        P(child_mutex);
        // increment the array
        arr[Curr_Thread->thread_id - 1]++;
        // wake up the parent
        V(parent_mutex);
    }
}

// Parent thread. Runs forever.
void parent(){
    while(1){
        int i, j;
        // put parent to sleep and switch to children
        for(j = 0; j < N; j++){
            P(parent_mutex);
        }
        // print the child threads
        print_arr(N);
        // wake up the children
        for(i = 0; i < N; i++){
            V(child_mutex);
        }
    }
}

// Prints the current thread array contents in proper format.
void print_arr(int size){
    int j, print_format;

    if(arr[0] < 10) {
        print_format = (size * 4) + 1;
    }else if(arr[0] < 100){
        print_format = (size * 5) + 1;
    }else if(arr[0] < 1000){
        print_format = (size * 6) + 1;
    }else if(arr[0] < 10000){
        print_format = (size * 7) + 1;
    }else if(arr[0] < 100000){
        print_format = (size * 8) + 1;
    }

    for(j = 0; j < print_format; j++){
        printf("-");
    }
    printf("\n");

    printf("|");
    for(j = 0; j < size; j++){
        printf(" %d |", arr[j]);
    }

    printf("\n");
    sleep(1);
}

// Describes program usage then exits.
void usage(){
    printf("\n\n[*] Usage: ./a.out <integer>\n\n");
    printf("[*] Requested thread parameter must be supplied from command line\n\n");
    printf("[*] Example:\n\n");
    printf("\t[>] User wants to run five threads in parallel:  ./a.out 5\n\n");
    printf("\t[>] User wants to exit application:  <CTRL+C>\n\n");
    exit(1);
}

// Entry main.  Command line parameter required.
int main(int argc, char ** argv){
    // check the command line arguments
    if(argc != 2){
        usage();
    }else{
        N = atoi(argv[1]);
    }
    printf("\n\nEnter <CTRL+C> to exit\n\n");
    sleep(1);
    // initialize array
    arr = (int*) malloc(N * sizeof(int));

    int i;
    for(i = 0; i < N; i++){
        arr[i] = 0;
    }
    // initialize the queue
    ReadyQ = newQueue();

    parent_mutex = (Semaphore*) malloc(sizeof(Semaphore));
    child_mutex = (Semaphore*) malloc(sizeof(Semaphore));
    // initialize semaphores
    InitSem(parent_mutex, N-1);
    InitSem(child_mutex, N);
    // point function pointers and start threads
    parent_ptr = parent;
    start_thread(parent_ptr);
    for(i = 0; i < N; i++) {
        child_ptr = child;
        start_thread(child_ptr);
    }
    // run the threads
    run();
}
