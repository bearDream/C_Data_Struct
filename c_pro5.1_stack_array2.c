#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 20

typedef struct Stack{
    int data[MAXSIZE];
    int top_front; // 堆栈1的指针位置
    int top_tail; // 堆栈2的指针位置
}Stack;

Stack *create(void);
void push(Stack *, int, int);
int pop(Stack *, int);
bool isEmpty(Stack *);
bool isFull(Stack *);
void show_stack(Stack *);

// 堆栈的顺序结构实现 一个数组存储两个堆栈
// 两个堆栈分别从数组的左右两端向中间存储
int main(int argc, char const *argv[])
{
    Stack *stack = create();
    push(stack, 10, 1);
    push(stack, 11, 1);
    push(stack, 12, 1);
    push(stack, 13, 1);

    push(stack, 210, 2);
    push(stack, 211, 2);
    push(stack, 212, 2);
    show_stack(stack);
    printf("pop stack 1 is %d \n", pop(stack, 1));
    printf("pop stack 2 is %d \n", pop(stack, 2));
    show_stack(stack);
    return 0;
}

Stack *create(){
    Stack *stack = malloc(sizeof(Stack));
    stack -> top_front = -1;
    stack -> top_tail = MAXSIZE;
    return stack;
}

// tag 标志对栈1操作还是对栈2操作
void push(Stack *stack, int val, int tag){
    if(stack->top_tail - stack->top_front == 1){
        perror("堆栈已满..不能进行压栈操作");
        return;
    }
    if(tag == 1){
        stack->data[++(stack->top_front)] = val;
        printf("after push front: %d  top is %d\n", stack->data[stack->top_front], stack->top_front);
        return;
    }else if(tag == 2){
        stack->data[--(stack->top_tail)] = val;
        printf("after push tail: %d  top is %d\n", stack->data[stack->top_tail], stack->top_tail);
        return;
    }else{
        stack->data[++(stack->top_front)] = val;
        printf("默认对栈1进行压栈操作\n");
        return;
    }
}


int pop(Stack *stack, int tag){
    if(tag == 1){
        // 若栈1为空，则无法出栈
        if(stack->top_front == 0){
            perror("堆栈1为空..不能进行出栈操作");
            return -1;
        }else{
            return stack->data[(stack->top_front)--];
        }
    }else if(tag==2){
        // 若栈2为空，则无法出栈
        if(stack->top_front == MAXSIZE-1){
            perror("堆栈2为空..不能进行出栈操作");
            return -1;
        }else{
            return stack->data[(stack->top_tail)++];
        }
    }else{
        perror("tag 有错");
        return -1;
    }
}

void show_stack(Stack *stack){
    // show stack1
    if(stack->top_front!=0){
        printf("栈1:");
        for(int t=0; t <= stack->top_front; t++){
            printf(" %d ", stack->data[t]);
        }
    }
    puts("");
    // show stack2
    if(stack->top_tail!=MAXSIZE-1){
        printf("栈2:");
        for(int t=MAXSIZE-1; t >= stack->top_tail; t--){
            printf(" %d ", stack->data[t]);
        }
    }
    puts("");
}