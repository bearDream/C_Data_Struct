#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;
typedef struct TreeNode *BinTree;

BinTree find_recursive(int, BinTree);
BinTree find_foreach(int, BinTree);
TreeNode *find_min(BinTree);
TreeNode *find_max(BinTree);
// TreeNode *create_BST(BinTree);
void print_BST(BinTree);

TreeNode *insert_tree(int, BinTree);
TreeNode *delete_tree(int, BinTree);

// 二叉搜索树BST 操作
int main(int argc, char const *argv[])
{
    TreeNode *t_node = NULL;
    t_node = insert_tree(10, t_node);
    insert_tree(5, t_node);
    insert_tree(2, t_node);
    insert_tree(8, t_node);
    insert_tree(12, t_node);
    print_BST(t_node);
    puts("");

    printf("100 in %p address position of tree.\n", find_recursive(100, t_node));
    printf("5 in %p position of tree.\n", find_foreach(5, t_node));
    printf("the element of min is %p.\n", find_min(t_node));
    printf("the element of max is %p.\n", find_max(t_node));
    
    printf("delete element %p.\n", delete_tree(12, t_node));
    print_BST(t_node);

    
    return 0;
}

// 递归实现查找
BinTree find_recursive(int element, TreeNode *node){
    if(node == NULL){
        printf("element: %d can not find.\n", element);
        return NULL;
    }else if(node->data > element){
        return find_recursive(element, node->left);
    }else if(node->data < element){
        return find_recursive(element, node->right);
    }else
        // find element.
        return node;
}

// 迭代循环实现查找
BinTree find_foreach(int element, TreeNode *node){
    if(node == NULL){
        printf("element: %d can not find.\n", element);
        return NULL;
    }
    while(node){
        if(node->data > element){
            node = node->left;
        }else if(node->data < element){
            node = node->right;
        }else{
            return node;
        }
    }
    return NULL;
}

TreeNode *find_min(TreeNode *node){
    if(!node) return NULL;
    if(node->left){
        return find_min(node->left);
    }
    return node;
}

TreeNode *find_max(TreeNode *node){
    if(!node) return NULL;
    if(node->right){
        return find_max(node->right);
    }
    return node;
}

TreeNode *insert_tree(int val, TreeNode *node){
    TreeNode *new_node = (TreeNode *) malloc(sizeof(TreeNode));
    new_node->left = NULL; new_node->right = NULL;
    new_node->data = val;
    if(node == NULL){
        return new_node;
    }else if(node->data > val){
        node->left = insert_tree(val, node->left);
    }else if(node->data < val){
        node->right = insert_tree(val, node->right);
    }
    return node;
}


// tranvarsal BST
void print_BST(TreeNode *node){
    if(node){
        printf("%d ", node->data);
        print_BST(node->left);
        print_BST(node->right);
    }
}

/*
*   删除节点的三种情况
*   1. 该节点有左子树，也有右子树
*   2. 该节点有一个子节点，或没有子节点
*/
TreeNode *delete_tree(int val, TreeNode *node){
    TreeNode *tmp = (TreeNode *) malloc(sizeof(TreeNode));
    if(!node)
        printf("element %d not exist.\n", val);
    else if(val < node->data)
        node->left = delete_tree(val, node->left);
    else if(val > node->data)
        node->right = delete_tree(val, node->right);
    else{
        if(node->left && node->right){ // have two child nodes.
            tmp = find_max(node->right);
            node->data = tmp->data;
            node->right = delete_tree(val, node->right);
        }else{ // have one child node or no child node.
            tmp = node;
            if(node->left == NULL){
                tmp = node->right;
                free(node);
                return tmp;
            }else if(node->right == NULL){
                tmp = node ->left;
                free(node);
                return tmp;
            }
        }
    }
    return node;
}