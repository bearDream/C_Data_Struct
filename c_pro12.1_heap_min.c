#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MINDATA -2147483647
#define MAXCAP 100

typedef struct Heap *MinHeap;
struct Heap{
    int *elements; // 存储的元素数组
    int capacity; // 堆的最大容量
    int size; // 堆的当前元素数
};

MinHeap create_heap();
void insert_heap(int, MinHeap);
void *delete_heap(MinHeap); // 堆每次删除的元素都是最小的元素
bool is_empty(MinHeap);
bool is_full(MinHeap);
void print_heap(MinHeap);


int main(int argc, char const *argv[])
{
    MinHeap tree = create_heap();
    insert_heap(5, tree);
    insert_heap(7, tree);
    insert_heap(10, tree);
    insert_heap(8, tree);
    insert_heap(9, tree);
    insert_heap(12, tree);
    insert_heap(3, tree);

    puts("====before delete====");
    print_heap(tree);
    puts("===after delete===");
    delete_heap(tree);
    print_heap(tree);
    return 0;
}


MinHeap create_heap(){
    MinHeap node = malloc(sizeof(MinHeap));
    node->elements = malloc((MAXCAP + 1) * sizeof(int));
    node->size = 0;
    node->capacity = MAXCAP;
    node->elements[0] = MINDATA;
    return node;
}

void insert_heap(int item, MinHeap h){
    if(is_full(h)){
        puts("heap is full..can not insert element.\n");
        return;
    }
    int i;
    i = ++h->size;
    while(h->elements[i/2] > item && i>1){
        h->elements[i] = h->elements[i/2];
        i /= 2;
    }
    h->elements[i] = item;
}


void *delete_heap(MinHeap h){
    if(is_empty(h)){
        puts("heap is empty..can not delete any elements.\n");
        return -1;
    }

    void *min_item = h->elements[1]; // min_item保留第一个元素(即最小的元素)
    int temp = h->elements[h->size--]; // temp保留最后一个元素
    int parent, child;
    for(parent=1; parent * 2 <= h->size; parent = child){
        child = parent * 2;
        if(h->elements[child] > h->elements[child+1])
            child++;
        if(temp >= h->elements[child])
            h->elements[parent] = h->elements[child];
        else 
            break;
    }
    h->elements[parent] = temp;
    return min_item;
}

void print_heap(MinHeap h){
    int size = h->size;
    for(int i=1; i <= size; i++)
        printf("%d \n", h->elements[i]);
}

bool is_empty(MinHeap h){
    if(h == NULL || h->size == 0) return true;
    else return false;
}

bool is_full(MinHeap h){
    if(h->size == MAXCAP) return true;
    else return false;
}