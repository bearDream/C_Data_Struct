#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 20

typedef struct Stack{
    int data[MAXSIZE];
    int top;
}Stack;

Stack *create(void);
void push(Stack *, int);
int pop(Stack *);
bool isEmpty(Stack *);
bool isFull(Stack *);

// 堆栈的顺序结构实现 一个数组只存储一个堆栈
int main(int argc, char const *argv[])
{
    Stack *stack = create();
    push(stack, 10);
    push(stack, 20);
    printf("stack val is %d \n", stack->data[1]);
    printf("pop stack element is %d\n", pop(stack));
    printf("stack top is %d \n", stack->top);
    return 0;
}

Stack *create(){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->data[0] = 0;
    stack->top = 0;
    return stack;
}

void push(Stack *stack, int val){
    if(isFull(stack)){
        perror("堆栈已满..不能进行压栈操作\n");
        return;
    }
    stack->data[++(stack->top)] = val;
}

int pop(Stack * stack){
    if(isEmpty(stack)){
        perror("堆栈为空..不能进行出栈操作\n");
        return -1;
    }
    return (stack->data[--(stack->top)]);
}

bool isFull(Stack *stack){
    if(stack -> top == MAXSIZE-1)
        return true;
    else
        return false;
}

bool isEmpty(Stack *stack){
    if(stack -> top == 0)
        return true;
    else
        return false;
}