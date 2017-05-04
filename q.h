/*
*                       q.h
*
*	Authors:			Jacob Loden, Nathan Chancellor
*						CSE330
*						Fall 2016
*						Tu, Thurs
*
*	Description:	    Project 4
*
*						Creates new, adds elements to, and returns first element of queue data structure.
*						Queue follows a circular doubly linked list structure, with the first element being a
*						blank "dummy" element pointed to by the "head" pointer.
*
*						Head => Dummy => Queue data => Dummy
*									  <=
*
*						Follows a first in first out return policy.
*
*/

#ifndef CSE330_PROJ_1_Q_H
#define CSE330_PROJ_1_Q_H
#define MAX_QUEUE 100

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include "tcb.h"

TCB_t* newItem();
TCB_t* newTcb(TCB_t* head);
void AddTcb(TCB_t* head_node, TCB_t* new_node);
TCB_t* DelTcb(TCB_t* head);
void DelAll(TCB_t* del_item);
void PrintTcb(TCB_t* head);
void flush();


//Creates and returns new struct node
struct TCB_t* newItem(){
    TCB_t* new_tcb;            //create new node on heap
    new_tcb = (TCB_t*) malloc(sizeof(TCB_t));
    return new_tcb;                        //return the new node
}

//Creates new empty queue structure. Returns head element.
TCB_t* newQueue(){
    TCB_t *dummy = newItem();   //create dummy node
    TCB_t *head = newItem();

    dummy->next = NULL;                     //set dummy elements to NULL
    dummy->prev = NULL;

    head->next = dummy;                     //point head at dummy
    head->prev = NULL;

    return head;                            //return head
}

//Add new item to queue
void AddTcb(TCB_t* head_tcb_node, TCB_t* new_tcb_node){
    TCB_t* tmp, *dummy;
    dummy = head_tcb_node->next;      //tmp is header node

    if(dummy->next == NULL){
        dummy->next = new_tcb_node;
        dummy->prev = new_tcb_node;
        new_tcb_node->next = dummy;
        new_tcb_node->prev = dummy;
    }else{
        tmp = dummy->next;
        while(tmp->next != dummy){
            tmp = tmp->next;
        }
        new_tcb_node->next = tmp->next;
        new_tcb_node->prev = tmp;
        tmp->next = new_tcb_node;
        dummy->prev = new_tcb_node;
    }

}

//Remove and return first queue element. Returns NULL if queue is empty.
TCB_t* DelTcb(TCB_t *head){
    if(head == NULL || head->next == NULL){
        printf("Error: Queue empty");
        return NULL;
    }

    TCB_t *dummy, *pop, *tmp;
    dummy = head->next;

    if (dummy->next == NULL){
        printf("Error: Queue empty");
        pop = NULL;
    }else{
        pop = dummy->next;
        if(pop->next == dummy){
            dummy->next = NULL;
            dummy->prev = NULL;
        }else{
            tmp = pop->next;
            tmp->prev = dummy;
            dummy->next = tmp;
        }
        pop->next = pop->prev = NULL;
    }
    return pop;
}

//Free all memory on exit
void DelAll(TCB_t* head){
    TCB_t* tmp;
    tmp = head->next;
    if(tmp->next == NULL){
        free(tmp);
        free(head);
    }else{
        tmp = tmp->next;
        while(tmp != head->next){
            TCB_t *del = tmp;
            free(del);
            tmp = tmp->next;
        }
        free(tmp);
        free(head);
    }
}

//Print queue
void PrintTcb(TCB_t* head){
    TCB_t* tmp = head->next;
    TCB_t* walk;
    if(tmp->next == NULL){
        printf("\n\nQueue empty!\n\n");
        return;
    }
    walk = tmp->next;
    int i = 0;
    printf("\n");
    while(walk != tmp){
        printf("Queue Element: %d\t", i);
        printf("Data: %d\n", walk->thread_id);
        i += 1;
        walk = walk->next;
    }
    printf("\n");
}

//Flush input buffer
void flush(){
    int c;
    do{
        c = getchar();
    }while(c != '\n' && c != EOF);
}

#endif //CSE330_PROJ_1_Q_H
