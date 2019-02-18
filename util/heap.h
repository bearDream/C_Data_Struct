#ifndef _HEAP_H
#define _HEAP_H

#include "./util.h"

#define MAXDATA 2147483647
#define MAXCAP 100

typedef struct Heap *MaxHeap;
struct Heap{
    int *elements; // 存储的元素数组
    int capacity; // 堆的最大容量
    int size; // 堆的当前元素数
};

// 创建的堆。从第0个元素开始排起
MaxHeap create_heap();
void adjust_heap(int[], int, int); //调整堆 @param array,  adjust vertex index,  size
void insert_heap(int, MaxHeap);
int delete_heap(MaxHeap); // 堆每次删除的元素都是最大(小)的元素
bool is_heap_empty(MaxHeap);
bool is_heap_full(MaxHeap);
void print_heap(MaxHeap);

#endif