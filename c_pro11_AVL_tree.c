#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode{
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
}TreeNode;

int max(int, int);
int height(TreeNode *);
struct TreeNode *new_node(int);
struct TreeNode *right_rotate(TreeNode *);
struct TreeNode *left_rotate(TreeNode *);
struct TreeNode *insert_node(int, TreeNode *);
int get_balance(TreeNode *);
void pre_tranversal(TreeNode *);

/*
* The AVL tree are more balanced than red-black tree.
* But the AVL tree may cause more rotations during insertion and deletion.
* So if your application involves many frequent insertion and deletion, then red-black tree is perfected.
* And if the insertions and deletion are less frequent and search is the more frequent, then AVL tree is perfected.  
*/
int main(int argc, char const *argv[])
{
    struct TreeNode *tree = NULL;
    tree = insert_node(6, tree);
    tree = insert_node(4, tree);
    tree = insert_node(10, tree);
    tree = insert_node(3, tree);
    tree = insert_node(5, tree);
    tree = insert_node(7, tree);
    tree = insert_node(8, tree);
    tree = insert_node(25, tree);
    tree = insert_node(27, tree);

    pre_tranversal(tree);


    // printf("node add is %d\n", tree->left->key);
    return 0;
}


struct TreeNode *right_rotate(TreeNode *tree){
    TreeNode *x = tree->left;
    TreeNode *T3 = x->right;

    // the order can be reversed.
    tree->left = T3;
    x->right = tree;

    // update tree heights
    tree->height = (height(tree->left) - height(tree->right)) + 1;
    x->height = (height(x->left) - height(x->right)) + 1;
    return x;
}

struct TreeNode *left_rotate(TreeNode *tree){
    TreeNode *x = tree->right;
    TreeNode *T2 = x->left;

    tree->right = T2;
    x->left = tree;

    tree->height = (height(tree->left) - height(tree->right)) + 1;
    x->height = (height(x->left) - height(x->right)) + 1;

    return x;
}

// ========= AVL core =========
// refer https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
struct TreeNode *insert_node(int key, TreeNode *tree){
    // 1. insert node
    if(tree == NULL)
        return new_node(key);
    // recursive insert.
    if(key < tree->key)
        tree->left = insert_node(key, tree->left);
    else if(key > tree->key)
        tree->right = insert_node(key, tree->right);
    else // equal keys are not allowed in AVL tree. 
        return tree;

    // 2. update height
    tree->height = 1 + max(height(tree->left), height(tree->right));
    // 3. update balance
    int balance = get_balance(tree);


    // 4. rotate tree if balance greater than 1
    // 4 case.

    // LL case
    if(balance > 1 && key < tree->left->key){
        return right_rotate(tree);
    }

    // LR case
    if(balance > 1 && key > tree->left->key){
        tree->left = left_rotate(tree->left);
        return right_rotate(tree);
    }

    // RR case
    if(balance < -1 && key > tree->right->key){
        return left_rotate(tree);
    }

    // RL case
    if(balance < -1 && key < tree->right->key){
        tree ->right= right_rotate(tree->right);
        return left_rotate(tree);
    }

    // if unchanged. return node.
    return tree;
}

void pre_tranversal(TreeNode *tree){
    if(tree != NULL){
        printf("%d ", tree->key);
        pre_tranversal(tree->left);
        pre_tranversal(tree->right);
    }
}

int get_balance(TreeNode *tree){
    if(tree == NULL)
        return 0;
    return height(tree->left) - height(tree->right);
}

struct TreeNode *new_node(int key){
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(TreeNode *node){
    if(node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}