#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A Huffman tree node
typedef struct MinHeapNode{
    char data;
    int weight;
    struct MinHeapNode *left;
    struct MinHeapNode *right;
}MinHeapNode;

// A Min Heap
typedef struct MinHeap{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
}MinHeap;

MinHeapNode* new_node(char, int);
MinHeap* create_min_heap(unsigned);
MinHeap* create_build_min_heap(char[], int[], int);
MinHeapNode* extract_min_heap(MinHeap*);
MinHeapNode* build_huffman_tree(char[], int[], int);

void build_min_heap(MinHeap*);
void insert_min_heap(MinHeap*, MinHeapNode*);
void min_heap_ify(MinHeap*, int);

// utils
void swap_min_heap_node(MinHeapNode **, MinHeapNode **);
bool is_empty(MinHeap*);
bool is_full(MinHeap*);
bool is_leaf(MinHeapNode*);
void print_tree(MinHeap*);
void print_codes(MinHeapNode*, int[], int);

/*
 * Huffman 树 
 * 最优路径树
 * 基于 最小堆 的数据结构实现
 */
int main(int argc, char const *argv[])
{
    MinHeap *heap = create_min_heap(100);
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int weight[] = { 10, 9, 8, 7, 6, 5 };
    int size = sizeof(data) / sizeof(data[0]);

    int arr[100], top=0;
    MinHeapNode *node = build_huffman_tree(data, weight, size);
    print_codes(node, arr, top);

    return 0;
}

// ================== Min Heap Build===========================
MinHeap* create_build_min_heap(char data[], int weight[], int size){
    MinHeap *heap = create_min_heap(size);
    for(int i=0; i < size; i++)
        heap->array[i] = new_node(data[i], weight[i]);
    heap->size = size;
    build_min_heap(heap);

    return heap;
}

// build a min heap. use @method min_heap_ify(MinHeap*, int)
void build_min_heap(MinHeap* h){
    int n = h->size - 1;
    for(int i=(n-1)/2; i >= 0; i--){
        min_heap_ify(h, i);
    }
}

void min_heap_ify(MinHeap* h, int n){
    int smallest = n;
    int left = n*2 + 1;
    int right = n*2 + 2;

    if(left < h->size && h->array[left]->weight < h->array[smallest]->weight)
        smallest = left;
    if(right < h->size && h->array[right]->weight < h->array[smallest]->weight)
        smallest = right;
    if(smallest != n){
        swap_min_heap_node(&h->array[smallest], &h->array[n]);
        min_heap_ify(h, smallest);
    }
}

// 插入一个元素入堆
void insert_min_heap(MinHeap* h, MinHeapNode* element){
    if(is_full(h)){
        puts("heap is full. can not insert a new node.\n");
        return;
    }
    ++h->size;
    int i = h->size - 1; // 存储的数组从0开始的，因此要减1

    while(i && element->weight < h->array[(i - 1) / 2]->weight){
        h->array[i] = h->array[(i-1) / 2];
        i = (i-1) / 2;
    }

    h->array[i] = element;
}

// 取出一个堆顶元素，即堆的最小值
MinHeapNode* extract_min_heap(MinHeap* h){
    if(is_empty(h)){
        puts("heap is empty, can not extract min node.");
        return NULL;
    }
    if(h->size == 1){
        return h->array[--h->size];
    }
    MinHeapNode *n = h->array[0];
    h->array[0] = h->array[h->size-1];
    --h->size;
    min_heap_ify(h, 0);
    return n;
}

// ================== HuffMan tree/code Build===========================
MinHeapNode* build_huffman_tree(char data[], int weight[], int size){
    MinHeapNode *T;
    MinHeap *h;

    h = create_build_min_heap(data, weight, size);
    while(h->size != 1){
        T = (MinHeapNode*) malloc(sizeof(MinHeapNode));
        T->left = extract_min_heap(h);
        T->right = extract_min_heap(h);
        // printf("T left is %d ", T->left->weight);
        // printf("T right is %d \n", T->right->weight);

        T->data = '$';// T 为两个元素合并出来的新元素，不做最后输出的叶子节点所用，因此用特殊符号占位
        T->weight = T->left->weight + T->right->weight;
        insert_min_heap(h, T);
    }
    T = extract_min_heap(h);
    return T;
}


//======================utils===========================

bool is_empty(MinHeap* h){
    if(h->size == 0) return true;
    else return false;
}


bool is_full(MinHeap* h){
    if(h->size == h->capacity) return true;
    else return false;
}

void print_tree(MinHeap *h){
    puts("minheap tree is: ");
    for(int i=0; i < h->size; i++){
        printf("%d ", h->array[i]->weight);
    }
    puts("");
}

// print codes from root of HuffMan tree
void print_codes(MinHeapNode* element, int arr[], int top){

    // left router is 0
    if(element->left){
        arr[top] = 0;
        print_codes(element->left, arr, top+1);
    }

    // left router is 1
    if(element->right){
        arr[top] = 1;
        print_codes(element->right, arr, top+1);
    }

    // if the node is the leaf node, it is a haffman code.
    if(is_leaf(element)){
        // print element value
        printf("%c ", element->data);
        // print element haffman code
        for(int i=0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }

}


void swap_min_heap_node(MinHeapNode **a, MinHeapNode **b){
    MinHeapNode *temp = *a;
    *a = *b;
    *b = temp;
}

MinHeapNode* new_node(char data, int weight){
    MinHeapNode *node = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    node->data = data;
    node->weight = weight;
    node->left = NULL;
    node->right = NULL;
    return node;
}

MinHeap* create_min_heap(unsigned capacity){
    MinHeap *h = (MinHeap *) malloc(sizeof(struct MinHeap));
    h->size = 0;
    h->capacity = capacity;
    h->array = (MinHeapNode**) malloc(h->capacity * sizeof(MinHeapNode));
    return h;
}

bool is_leaf(MinHeapNode* node){
    return !node->left && !node->right;
}