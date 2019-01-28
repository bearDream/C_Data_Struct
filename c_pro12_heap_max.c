#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXDATA 2147483647
#define MAXCAP 100

typedef struct Heap *MaxHeap;
struct Heap{
    int *elements; // 存储的元素数组
    int capacity; // 堆的最大容量
    int size; // 堆的当前元素数
};

MaxHeap create_heap();
void insert_heap(int, MaxHeap);
int delete_heap(MaxHeap); // 堆每次删除的元素都是最大(小)的元素
bool is_empty(MaxHeap);
bool is_full(MaxHeap);
void print_heap(MaxHeap);


// 大顶堆: 完全二叉树的存储结构，且每个节点都比子节点大(小顶堆与之相反)
// 小顶堆在工具类里封装
int main(int argc, char const *argv[])
{
    MaxHeap head = create_heap();
    insert_heap(70, head);
    insert_heap(60, head);
    insert_heap(65, head);
    insert_heap(50, head);
    insert_heap(55, head);
    insert_heap(59, head);

    print_heap(head);
    printf("delete %d\n", delete_heap(head));
    print_heap(head);
    printf("delete %d\n", delete_heap(head));
    print_heap(head);    
    return 0;
}

MaxHeap create_heap(){
    MaxHeap node = malloc(sizeof(MaxHeap));
    node->elements = malloc((MAXCAP + 1) * sizeof(int));
    node->size = 0;
    node->capacity = MAXCAP;
    node->elements[0] = MAXDATA;
    return node;
}

void insert_heap(int item, MaxHeap h){
    int i;
    if(is_full(h)){
        printf("heap is full, can not insert element.\n");
        return;
    }

    i = ++h->size; // i指使的为堆数组中最后一位
    while(h->elements[i/2] < item && i > 1){
        h->elements[i] = h->elements[i/2]; // 从下往上回朔，将比节点大的元素往下移
        i /= 2; // 指示的位置往上继续移动
    }
    h->elements[i] = item;
}

int delete_heap(MaxHeap h){
    if(is_empty(h)){
        puts("heap is empty, can not delete.\n");
        return -1;
    }
    int max_item, temp;
    // 1. temp变量保存树中序号最大的一个元素，且删除了序号最大的元素
    temp = h->elements[h->size--];
    max_item = h->elements[1];
    int parent, child;
    for(parent=1; parent*2 <= h->size; parent=child){
        child = parent * 2;
        // 保证从根往下找位置时，总找的是元素较大的一颗树
        if((child != h->size) && h->elements[child] < h->elements[child+1])
            child++;
        if(temp >= h->elements[child]) break;
        else h->elements[parent] = h->elements[child];
    }
    // 将序号最大的元素替换在找到的parent位置
    h->elements[parent] = temp;
    return max_item;
}

void print_heap(MaxHeap h){
    int size = h->size;
    for(int i=1; i <= size; i++)
        printf("%d \n", h->elements[i]);
}

bool is_empty(MaxHeap h){
    if(h == NULL || h->size == 0) return true;
    else return false;
}

bool is_full(MaxHeap h){
    if(h->size == MAXCAP) return true;
    else return false;
}