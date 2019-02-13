#include <stdbool.h>
#include "util/util.h"

#define RAND_UPPER 1000
#define RAND_LOWER 1

void *init_array(int[], int); // 生成随机数组
void *bubble_sort(int [], int); // 冒泡排序
void *insert_sort(int [], int); // 插入排序

void print_array(int [], int size);

int main(int argc, char const *argv[]){
    int size = 10;
    int arr[size];
    init_array(arr, size);
    puts("orginal array:");
    print_array(arr, size);

    insert_sort(arr, size);
    puts("after bubble sort:");
    print_array(arr, size);
    
    return 0;
}

void *bubble_sort(int array[], int size){
    bool flag = true;
    for(int i = size-1; i >= 0; i--){
        flag = true;
        for(int j = 0; j < i; j++){
            if (array[j] > array[j+1]) {
                // 交换两数
                array[j] = array[j]^array[j+1];
                array[j+1] = array[j+1] ^ array[j];
                array[j] = array[j] ^ array[j+1];
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

void *init_array(int array[], int size){
    for(int i = 0; i < size; i++){
        array[i] = get_rand(RAND_LOWER, RAND_UPPER);
    }
    return array;
}

void print_array(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}