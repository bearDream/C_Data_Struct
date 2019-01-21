#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct LinkQueue{
    struct QueueNode *front;
    struct QueueNode *rear;
}LinkQueue;

typedef struct QueueNode{
    int data;
    struct QueueNode *next;
}QueueNode;

LinkQueue *createQ(LinkQueue *);
void addQ(LinkQueue *, int);
int delQ(LinkQueue *);
bool isEmpty(LinkQueue *);
void printQ(LinkQueue);

// 队列的链式存储结构, 不存在浪费空间的情况，因此设计为顺序链表
int main(int argc, char const *argv[])
{
    LinkQueue *ptrQ;
    ptrQ = createQ(ptrQ);

    addQ(ptrQ, 10);
    addQ(ptrQ, 11);
    addQ(ptrQ, 12);
    addQ(ptrQ, 13);
    addQ(ptrQ, 14);
    printf("del element: %d \n", delQ(ptrQ));
    printf("del element: %d \n", delQ(ptrQ));
    printQ(*ptrQ);

    return 0;
}

LinkQueue *createQ(LinkQueue *ptrQ){
    QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
    ptrQ = (LinkQueue *) malloc(sizeof(LinkQueue));
    ptrQ->front = node;
    ptrQ->rear = ptrQ->front;
    return ptrQ;
}

// front 删除操作
void addQ(LinkQueue *queue, int val){
    QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));

    node->data = val;
    node->next = NULL;
    
    queue->rear->next = node;
    queue->rear = node;
    return;
}

// rear 添加操作
int delQ(LinkQueue *queue){
    if(isEmpty(queue)){
        puts("Warning: queue is empty.\n");
        return -1;
    }

    QueueNode *node = queue->front->next;
    int val = node->data;

    queue->front = node->next;
    queue->front = node;
    free(node);
    return val;
}

bool isEmpty(LinkQueue *queue){
    return queue->front->next == NULL ? true : false;
}

void printQ(LinkQueue queue){
    LinkQueue q = queue;
    printf("Queue:");
    while(!isEmpty(&q)){
        q.front = q.front->next;
        printf("%d ", q.front->data);
    }
}