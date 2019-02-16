#include <stdbool.h>
#include "util/util.h"
#include "util/heap.h"

#define RAND_UPPER 1000
#define RAND_LOWER 1

void *init_array(int[], int); // 生成随机数组
void *selection_sort(int [], int); // 选择排序
void *bubble_sort(int [], int); // 冒泡排序
void *insert_sort(int [], int); // 插入排序
void *shell_sort(int [], int); // 希尔排序
void *heap_sort(int [], int); // 堆排序

void swap(int *, int *);
void print_array(int [], int size);
int find_min(int [], int, int);

int main(int argc, char const *argv[]){
    int size = 10;
    int arr[size];
    // 初始化随机数据
    init_array(arr, size);
    puts("orginal array:");
    print_array(arr, size);

    // 选择排序
    // selection_sort(arr, size);
    // puts("after selection sort:");
    // print_array(arr, size);

    // 插入/冒泡排序
    bubble_sort(arr, size);
    puts("after bubble sort:");
    print_array(arr, size);
    
    // 希尔排序
    // shell_sort(arr, size);
    // puts("after shell sort:");
    // print_array(arr, size);
    return 0;
}

void *selection_sort(int arr[], int size){
    int min_pos;
    for(int i = 0; i < size; i++){
        min_pos = find_min(arr, i, size);
        if (min_pos == i) continue;
        // 交换两数
        swap(&arr[i], &arr[min_pos]);
    }
    return arr;
}

void *bubble_sort(int array[], int size){
    bool flag = true;
    for(int i = size-1; i >= 0; i--){
        flag = true;
        for(int j = 0; j < i; j++){
            if (array[j] > array[j+1]) {
                // 交换两数
                swap(&array[j], &array[j+1]);
                flag = false;
            }
        }
        if (flag) break; // 循环一圈没有交换过，则认定已经排序完成，无需继续循环
    }
    return array;
}

void *insert_sort(int array[], int size){
    int tmp, j;
    for(int i = 1; i < size; i++){
        tmp = array[i]; // 得到一个新数
        for(j = i; j > 0 && array[j-1] > tmp; j--) // 若新数比前面的小，则循环与前面的所有数比
            array[j] = array[j-1]; // 旧数挪位
        array[j] = tmp; // 新数落位
    }
    return array;
}

// 希尔排序，主要取决于步长
// 采用Sedgewick增量序列  (1, 5, 19, 41, 109...)  (9 * 4^i - 9 * 2^i + 1)
//  s = 4^i - 3* 2^i + 1; s = 9*4^i - 9*2^i + 1;  
void *shell_sort(int array[], int size){

    printf("shell----\n");
    int tmp, k;
    for(int D = size/2; D > 0; D/=2){ // 设步长
        // 插入排
        for(int j = D; j < size; j++){
            tmp = array[j];
            for(k = j; k >=D && array[k-D] > tmp; k-=D)
                array[k] = array[k-D];
            array[k] = tmp;
        }
    }
    return array;
    
}

void *init_array(int array[], int size){
    for(int i = 0; i < size; i++){
        array[i] = get_rand(RAND_LOWER, RAND_UPPER);
    }
    return array;
}

void swap(int *a, int *b){
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}

int find_min(int array[], int i, int size){
    int min_index = i;
    for(int j = i; j < size; j++){
        if (array[j] < array[min_index]) {
            min_index = j;
        }
    }
    return min_index;
}

void print_array(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}