#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 5

typedef struct Queue{
    int data[MAXSIZE];
    int front; // point front of first element.
    int rear;  // point last element.
}Queue;

Queue *create(int);
void printfQ(Queue *q);
void addQ(Queue*, int);
int delQ(Queue*);
bool isEmpty(Queue*);
bool isFull(Queue*);

/*
*   addQ(q, 1);
    addQ(q, 2);
    addQ(q, 3);
    addQ(q, 4);
    printf("q->front is %d\n", q->front);
    printf("del element is %d\n", delQ(q));
    addQ(q, 5);
*
*
*/
// 队列的顺序存储结构, 循环队列
int main(int argc, char const *argv[])
{
    Queue *q = create(3);
    // addQ(q, 1);
    // addQ(q, 2);
    // addQ(q, 3);
    // addQ(q, 4);
    // printf("q->front is %d\n", q->front);
    // printf("del element is %d\n", delQ(q));
    // printf("del element is %d\n", delQ(q));
    // printf("del element is %d\n", delQ(q));
    // addQ(q, 5);
    // addQ(q, 6);
    // addQ(q, 7);
    addQ(q, 1);
    addQ(q, 2);
    addQ(q, 3);
    addQ(q, 4);
    printf("q->front is %d\n", q->front);
    printf("del element is %d\n", delQ(q));
    addQ(q, 5);
    printfQ(q);

    return 0;
}

// 只存储n-1个元素
Queue *create(int size){
    Queue *q = (Queue*) malloc(sizeof(Queue));
    q->front=0;
    q->rear=0;
    return q;
}

void addQ(Queue *q, int val){
    if(isFull(q)){
        puts("queue is full. can not add element.");
        return;
    }
    q->rear = (q->rear+1) % MAXSIZE; //形成循环队列
    printf("rear is %d\n", q->rear);
    q->data[q->rear] = val;
    return;
}

int delQ(Queue *q){
    if(isEmpty(q)){
        puts("queue is empty. can not del element.");
        return -1;
    }
    q->front = (q->front+1) % MAXSIZE;
    return q->data[q->front];
}

bool isEmpty(Queue *q){
    if(q->front == q->rear)
        return true;
    else
        return false;
}

bool isFull(Queue *q){
    if((q->rear+1)%MAXSIZE == q->front)
        return true;
    else
        return false;
}

/*
* 注意循环变量front应该是+1取模，而不是累加。
*/
void printfQ(Queue *q){
    printf("q->front is %d\n", q->front);
    printf("q->rear is %d\n", q->rear);
    int front = q->front+1;
    printf("Queue: ");
    while(front%MAXSIZE != (q->rear)+1){
        if((front) % MAXSIZE == q->rear){
            printf("%d ", q->data[q->rear]);
            break;
        }
        printf("%d ", q->data[front]);
        front = (front+1)%MAXSIZE;
    }
}