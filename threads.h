/*
*                       threads.h
*
*	Authors:			Jacob Loden
*
*	Description:	   	Functions to create, initialize, run and print processor threads
*
*/
#include "q.h"

#define STACK_SIZE 8192

// Global TCB_t pointers
TCB_t *ReadyQ;
TCB_t *Curr_Thread;

void start_thread(void (*function) ());
void run();
void yield();
void print_id(TCB_t *tcb);
int get_id(TCB_t *tcb);

//Initialize the current thread and add it to the stack
void start_thread(void (*function) ()){
    int *stack;                     //stack pointer
    TCB_t *new_tcb;                 //new TCB

    stack = malloc(STACK_SIZE);
    new_tcb = (struct TCB_t*) malloc(sizeof(struct TCB_t));

    if(!new_tcb)
        printf("Memory fault");

    init_TCB(new_tcb, function, stack, STACK_SIZE);
    AddTcb(ReadyQ, new_tcb);
}

//Get the currently running thread context, switch to next stack thread
void run(){
    Curr_Thread = DelTcb(ReadyQ);
    ucontext_t parent;
    getcontext(&parent);    //get the current running context
    swapcontext(&parent, &(Curr_Thread->context)); //switch it to the next q element
}

//Switch context to the next stack thread
void yield(){
    TCB_t *prev_thread;
    AddTcb(ReadyQ, Curr_Thread);
    prev_thread = Curr_Thread;
    Curr_Thread = DelTcb(ReadyQ);
    swapcontext(&(prev_thread->context), &(Curr_Thread->context));
}

//Print thread ID of tcb
void print_id(TCB_t *tcb){
    printf("[>] Thread ID: %d", tcb->thread_id);
}

// Get thread id
int get_id(TCB_t *tcb){
    return tcb->thread_id;
}
