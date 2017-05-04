/*
*                       sem.h
*
*	Authors:			Jacob Loden
*
*	Description:	   	Semaphore implementation.
*
*						InitSem(semaphore, value): Function to initialize the value field
*						of created semaphore structure.
*
*						P(semaphore): Function to create critical section.
*
*						V(semaphore): Function to exit critical section.
*
*/

#ifndef CSE330_PROJ_3_SEM_H
#define CSE330_PROJ_3_SEM_H

#include "threads.h"

// Semaphore structure
typedef struct Semaphore{
    int value;
    TCB_t *tcb_q;
}Semaphore;

// Forward declarations
void InitSem(Semaphore *s, int value);
void P(Semaphore *s);
void V(Semaphore *s);

// Initialize the semaphore value and TCB_t queue
void InitSem(Semaphore *s, int value){
    s->value = value;
    s->tcb_q = newQueue();
}

// Semaphore wait function
void P(Semaphore *s){
    TCB_t *tmp;
    s->value--;

    if(s->value < 0){
        tmp = Curr_Thread;
        AddTcb(s->tcb_q, Curr_Thread);
        Curr_Thread = DelTcb(ReadyQ);
        swapcontext(&(tmp->context), &(Curr_Thread->context));
    }
}

// Semaphore start function
void V(Semaphore *s){
    TCB_t *tmp;
    s->value++;

    if(s->value <= 0){
        AddTcb(ReadyQ, DelTcb(s->tcb_q));
    }
    yield();
}

#endif //CSE330_PROJ_3_SEM_H
