#include "queue.h"

// 队列的链式存储结构, 不存在浪费空间的情况，因此设计为顺序链表
int main(int argc, char const *argv[])
{
    LinkQueue *ptrQ;
    ptrQ = create_queue(ptrQ);
    int *a, *b, *c, *d, *e;
    int a1=10, b1=11, c1=12, d1=13, e1=14;
    a = &a1;
    b = &b1;
    c = &c1;
    d = &d1;
    e = &e1;
    addQ(ptrQ, a);
    addQ(ptrQ, b);
    addQ(ptrQ, c);
    addQ(ptrQ, d);
    addQ(ptrQ, e);
    printf("del element: %d \n", *(int *)delQ(ptrQ));
    printf("del element: %d \n", *(int *)delQ(ptrQ));
    printQ(*ptrQ);

    return 0;
}

LinkQueue *create_queue(LinkQueue *ptrQ){
    QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
    ptrQ = (LinkQueue *) malloc(sizeof(LinkQueue));
    ptrQ->front = node;
    ptrQ->rear = ptrQ->front;
    return ptrQ;
}

// front 删除操作
void addQ(LinkQueue *queue, void *val){
    QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));

    node->data = val;
    node->next = NULL;
    
    queue->rear->next = node;
    queue->rear = node;
    return;
}

// rear 添加操作
void *delQ(LinkQueue *queue){
    if(isEmpty(queue)){
        puts("Warning: queue is empty.\n");
        return NULL;
    }

    QueueNode *node = queue->front->next;
    void *val = node->data;

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
        printf("%d ", *(int *)(q.front->data));
    }
}