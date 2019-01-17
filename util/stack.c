#include "stack.h"

// 堆栈的顺序结构实现 一个数组只存储一个堆栈
// int main(int argc, char const *argv[])
// {
//     Stack *stack = create();
//     push(stack, 'a');
//     push(stack, 'b');
//     printf("stack val is %c \n", stack->data[1]);
//     printf("pop stack element is %c\n", pop(stack));
//     printf("stack top is %c \n", stack->top);
//     return 0;
// }


Stack *create(){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->top = 0;
    return stack;
}

void push(Stack *stack, char val){
    if(isFull(stack)){
        perror("堆栈已满..不能进行压栈操作\n");
        return;
    }
    stack->data[++(stack->top)] = val;
}

char pop(Stack * stack){
    if(isEmpty(stack)){
        perror("堆栈为空..不能进行出栈操作\n");
        return '1';
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

char getTop(Stack *stack){
    if(stack->top == 0){
        puts("栈为空..");
        return '1';
    }else{
        return stack->data[stack->top];
    }
}