#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024

typedef struct Stack{
    void *data[MAXSIZE];
    int top;
}Stack;

Stack *create_stack(void);
void push(Stack *, void*);
void *pop(Stack *);
bool isEmpty(Stack *);
bool isFull(Stack *);
void *getTop(Stack *);

#endif