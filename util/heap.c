#include "heap.h"

// int main(int argc, char const *argv[])
// {
//     MaxHeap head = create_heap();
//     insert_heap(60, head);
//     insert_heap(65, head);
//     insert_heap(50, head);
//     insert_heap(55, head);
//     insert_heap(59, head);
//     insert_heap(70, head);

//     print_heap(head);
//     return 0;
// }


MaxHeap create_heap(){
    MaxHeap node = malloc(sizeof(MaxHeap));
    node->elements = malloc((MAXCAP + 1) * sizeof(int));
    node->size = 0;
    node->capacity = MAXCAP;
    return node;
}

void insert_heap(int item, MaxHeap h){
    int i;
    if(is_heap_full(h)){
        printf("heap is full, can not insert element.\n");
        return;
    }
    // // 若heap为空，则第一个元素插入在第一个位置
    if (is_heap_empty(h)) {
        h->elements[0] = item;
        ++h->size;
        return;
    }

    i = (++h->size)-1; // i指使的为堆数组中最后一位
    while(h->elements[i/2] < item && i > 0){
        h->elements[i] = h->elements[i/2]; // 从下往上回朔，将比节点大的元素往下移
        i /= 2; // 指示的位置往上继续移动
    }
    h->elements[i] = item;
}

int delete_heap(MaxHeap h){
    if(is_heap_empty(h)){
        puts("heap is empty, can not delete.\n");
        return -1;
    }
    int max_item, temp;
    // 1. temp变量保存树中序号最大的一个元素，且删除了序号最大的元素
    temp = h->elements[--h->size];
    max_item = h->elements[0];
    int parent, child;
    for(parent=1; parent*2 <= h->size; parent=child){
        child = parent * 2;
        // 保证从根往下找位置时，总找的是元素较大的一颗树
        if((child != h->size) && h->elements[child-1] < h->elements[child])
            child++;
        if(temp >= h->elements[child-1]) break;
        else h->elements[parent-1] = h->elements[child-1];
    }
    // 将序号最大的元素替换在找到的parent位置
    h->elements[parent-1] = temp;
    return max_item;
}

// 调整二叉树为堆结构，循环调用此函数可将一棵树调整为最大堆
// @param A:调整的跟节点索引
void adjust_heap(int arr[], int A, int size){
    int tmp, j;

    tmp = arr[A-1]; // 数组从0开始排起
    for(j = 2*A; j <= size; j*=2){
        
        // 找到较大叶子节点
        if (j<size && arr[j-1] < arr[j]) {
            j++;
        }

        // 若根节点大于较大的叶子节点则什么都不做，跳出循环，表示以调整完成
        if (arr[A-1] >= arr[j-1]) break;
        
        // 否则将根节点和较大叶子节点交换
        arr[A-1] = arr[j-1];
        A = j;
        arr[A-1] = tmp;
    }
    arr[A-1] = tmp;
}

void print_heap(MaxHeap h){
    int size = h->size;
    for(int i=0; i < size; i++)
        printf("%d \n", h->elements[i]);
}

bool is_heap_empty(MaxHeap h){
    if(h == NULL || h->size == 0) return true;
    else return false;
}

bool is_heap_full(MaxHeap h){
    if(h->size == MAXCAP) return true;
    else return false;
}