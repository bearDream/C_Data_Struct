#include <stdio.h>

#define MAXSIZE 10
int binary_search(int [MAXSIZE], int);

/*
* 二分查找有序数组
*/
int main(int argc, char const *argv[])
{
    int nums[MAXSIZE] = {1, 10, 11, 19, 30, 32, 41, 48, 60, 72};
    printf("enter numbers that need search..\n");
    int search_num;
    scanf("%d", &search_num);
    printf("%d 元素在数组中的 %d 位置\n", search_num, binary_search(nums, search_num));
    return 0;
}

// 返回target所在数组中的索引
int binary_search(int data[MAXSIZE], int target){
    int left, right, middle;
    left=1; right=MAXSIZE;
    while(left <= right){
        middle = (right + left) / 2;
        if(data[middle] == target){
            return middle+1; // 查找到目标索引
        }
        else if(data[middle] < target) left = middle + 1;
        else if(data[middle] > target) right = middle - 1;
    }
    return -1; // 查找不到，返回-1
}
