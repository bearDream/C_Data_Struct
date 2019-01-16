#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack{
    int val;
    struct Stack *next;
}Stack;

Stack *create(void);
void push(Stack *, int);
int pop(Stack *);
void print_stack(Stack *);

// 堆栈的链式结构实现
int main(int argc, char const *argv[])
{
    Stack *head = create();
    push(head, 1);
    push(head, 2);
    push(head, 3);
    printf("pop element is %d \n", pop(head));
    push(head, 22);
    print_stack(head);
    return 0;
}

Stack *create(){
    Stack *stack = malloc(sizeof(Stack));
    stack->next = NULL;
    return stack;
}

// 头节点不动，将头节点的next指向新节点
void push(Stack *stack, int data){
    Stack *new_node = malloc(sizeof(Stack));
    new_node->val = data;
    new_node->next = stack->next;
    stack->next = new_node;
}

int pop(Stack *stack){
    if(stack->next == NULL){
        printf("stack is empty.. can not pop \n");
        return -1;
    }
    Stack *temp_node = stack->next;
    int val = temp_node->val;
    stack->next = temp_node->next;
    free(temp_node);
    return val;
}

void print_stack(Stack *stack){
    if(stack == NULL){
        perror("stack is null..\n");
        return;
    }
    Stack *node = stack->next;
    while(node){
        printf("stack element is %d \n", node->val);
        node = node->next;
    }
}