#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "./util/stack.h"
#include "./util/queue.h"

typedef struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;
typedef struct TreeNode *BinTree;

Stack *stack;

// 递归实现 遍历
void pre_traversal_recursive(BinTree);
void mid_traversal_recursive(BinTree);
void post_traversal_recursive(BinTree);

// 栈实现 遍历
void pre_traversal_stack(BinTree);
void mid_traversal_stack(BinTree);
void post_traversal_stack(BinTree);

// 层序遍历
void lay_tranversal_queue(BinTree);
void lay_tranversal_stack(BinTree);

// 获取二叉树的所有叶子节点
void print_tree_leaf(BinTree);
// 求二叉树的高度
int get_tree_height(BinTree);

bool is_empty(BinTree);
TreeNode *create_node(int);

// binary tree operation
int main(int argc, char const *argv[])
{
    // 先序构造树
    TreeNode *node = create_node(1);
    node->left = create_node(2);
    node->right = create_node(3);
    node->left->right = create_node(4);
    node->right->left = create_node(5);
    node->left->right->left = create_node(6);
    node->left->right->right = create_node(7);

    // puts("---Tranversal by Recursive---");
    // puts("pre: \n");
    // pre_traversal_recursive(node);
    // puts("");
    // puts("middle: \n");
    // mid_traversal_recursive(node);
    // puts("");
    // puts("post: \n");
    // post_traversal_recursive(node);

    // puts("");
    // puts("---Tranversal by Stack---");
    // puts("pre: \n");
    // pre_traversal_stack(node);
    // puts("");
    // puts("middle: \n");
    // mid_traversal_recursive(node);
    // puts("");
    // puts("post: \n");
    // post_traversal_recursive(node);
    // puts("");

    // puts("---Tranversal by level---");
    // puts("--implication by Queue");
    // lay_tranversal_queue(node);
    // puts("");
    puts("--implication by Stack");
    lay_tranversal_stack(node);
    puts("");

    puts("--Print all leaves of tree--\n");
    print_tree_leaf(node);

    puts("--Height of Tree--\n");
    printf("tree height is %d \n", get_tree_height(node));c_pro10_bst.c
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

// 队列实现层序遍历
void lay_tranversal_queue(TreeNode *node){
    LinkQueue *ptrQ;
    ptrQ = create_queue(ptrQ);
    addQ(ptrQ, node);
    while(!isEmptyQ(ptrQ)){
        TreeNode *cur = delQ(ptrQ);
        printf("%d ", cur->data);
        if(cur->left){
            addQ(ptrQ, cur->left);
        }
        if(cur->right){
            addQ(ptrQ, cur->right);
        }
        free(cur);
    }
}

// 将层序遍历的队列换成栈
void lay_tranversal_stack(TreeNode *node){
    stack = create_stack();
    push(stack, node);
    while(!isEmpty(stack)){
        TreeNode *cur = pop(stack);
        printf("%d ", cur->data);
        if(cur->left)
            push(stack, cur->left);
        if(cur->right)
            push(stack, cur->right);
    }
}

void print_tree_leaf(TreeNode *node){
    if(node->left == NULL && node->right == NULL)
        printf("%d ", node->data);
    if(node->left)
        print_tree_leaf(node->left);
    if(node->right)
        print_tree_leaf(node->right);
}

// Height: max(left_tree, right_tree) + 1
int get_tree_height(TreeNode *node){
    int lh, rh;
    if(node){
        lh = get_tree_height(node->left);
        rh = get_tree_height(node->right);
        return lh >= rh ? lh+1 : rh+1;
    }
    return 0;
}