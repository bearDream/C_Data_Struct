#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024

typedef struct LinkQueue{
    struct QueueNode *front;
    struct QueueNode *rear;
}LinkQueue;

typedef struct QueueNode{
    void *data;
    struct QueueNode *next;
}QueueNode;

LinkQueue *create_queue(LinkQueue *);
void addQ(LinkQueue *, void*);
void *delQ(LinkQueue *);
bool isEmptyQ(LinkQueue *);
void printQ(LinkQueue);

#endif