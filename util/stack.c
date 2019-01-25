#include "stack.h"

// 堆栈的顺序结构实现 一个数组只存储一个堆栈
// int main(int argc, char const *argv[])
// {
//     Stack *stack = create_stack();
//     int *a;
//     int *b;
//     int val1 = 23;
//     int val2 = 24;
//     a = &val1;
//     b = &val2;
//     push(stack, a);
//     push(stack, b);
//     printf("stack top is %d \n", (stack->top));
//     printf("stack val is %d \n", *(int *)(stack->data[1]));
//     printf("pop stack element is %d\n", *(int *)(pop(stack)));
//     return 0;
// }


Stack *create_stack(){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->top = 0;
    return stack;
}

void push(Stack *stack, void *val){
    if(isFull(stack)){
        perror("堆栈已满..不能进行压栈操作\n");
        return;
    }
    stack->data[++(stack->top)] = val;
}

void *pop(Stack * stack){
    if(isEmpty(stack)){
        perror("堆栈为空..不能进行出栈操作\n");
        return NULL;
    }
    return (stack->data[(stack->top)--]);
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

void *getTop(Stack *stack){
    if(stack->top == 0){
        puts("栈为空..");
        return NULL;
    }else{
        return (stack->data[stack->top]);
    }
}