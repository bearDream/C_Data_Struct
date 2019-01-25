#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "./util/stack.h"

typedef struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;
typedef struct TreeNode *BinTree;
typedef BinTree Position;

Stack *stack;

// 递归实现 遍历
void pre_traversal_recursive(BinTree);
void mid_traversal_recursive(BinTree);
void post_traversal_recursive(BinTree);

// 栈实现 遍历
void pre_traversal_stack(BinTree);
void mid_traversal_stack(BinTree);
void post_traversal_stack(BinTree);
bool is_empty(BinTree);
TreeNode *create_node(int);

// binary tree operation
int main(int argc, char const *argv[])
{
    // 先序构造树
    TreeNode *node = create_node(1);
    node->left = create_node(2);
    node->right = create_node(3);
    node->left->left = create_node(4);
    node->left->right = create_node(5);
    node->right->right = create_node(6);

    puts("---Tranversal by Recursive---");
    puts("pre: \n");
    pre_traversal_recursive(node);
    puts("");
    puts("middle: \n");
    mid_traversal_recursive(node);
    puts("");
    puts("post: \n");
    post_traversal_recursive(node);

    puts("");
    puts("---Tranversal by Stack---");
    puts("pre: \n");
    pre_traversal_stack(node);
    puts("");
    puts("middle: \n");
    mid_traversal_recursive(node);
    puts("");
    puts("post: \n");
    post_traversal_recursive(node);
    puts("");
    return 0;
}

TreeNode *create_node(int val){
    TreeNode *bt = (TreeNode *) malloc(sizeof(TreeNode));
    bt->data = val;
    bt->left = NULL;
    bt->right = NULL;
    return bt;
}

// 递归实现
void pre_traversal_recursive(BinTree tree){
    if(tree){
        printf("%d ", tree->data);
        pre_traversal_recursive(tree->left);
        pre_traversal_recursive(tree->right);
    }
}
void mid_traversal_recursive(BinTree tree){
    if(tree){
        mid_traversal_recursive(tree->left);
        printf("%d ", tree->data);
        mid_traversal_recursive(tree->right);
    }
}
void post_traversal_recursive(BinTree tree){
    if(tree){
        post_traversal_recursive(tree->left);
        post_traversal_recursive(tree->right);
        printf("%d ", tree->data);
    }
}

// 栈实现
void pre_traversal_stack(TreeNode *node){
    stack = create_stack();
    while(node || !isEmpty(stack)){
        while(node){
            printf("%d ", node->data);
            push(stack, node);
            node = node->left;
        }
        if(!isEmpty(stack)){
            node = pop(stack);
            node = node->right;
        }
    }
}

void mid_traversal_stack(TreeNode *node){
    stack = create_stack();
    while(node || !isEmpty(stack)){
        while(node){
            push(stack, node);
            node = node->left;
        }
        if(!isEmpty(stack)){
            node = pop(stack);
            printf("%d ", node->data);
        }
        node = node->right;
    }
}

void post_traversal_stack(TreeNode *node){
    stack = create_stack();
    while(node || !isEmpty(stack)){
        while(node){
            push(stack, node);
            node = node->left;
        }
        if(!isEmpty(stack)){
            node = pop(stack);
            printf("%d ", node->data);
            node = node->right;
        }
    }
}