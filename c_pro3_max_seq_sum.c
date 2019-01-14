#include <stdio.h>
#include <stdlib.h>


// 最快算法，复杂度为o(N)
int cal_seq_num_N(int[], int);
// 最快算法，复杂度为o(N^2)
int cal_seq_num_N2(int[], int);

void show_array(int [], int);
void fix_array(int [], int);
void input_array(int [], int);
int generate_rand(void);


int main(int argc, char const *argv[])
{
    int res_N, res_N2 = 0;
    int size = 0;
    printf("enter a sequence size: \n");
    scanf("%d", &size);
    int array[size];
    fix_array(array, size);

    printf("array max sequence is ");
    show_array(array, size);
    res_N = cal_seq_num_N(array, size);
    puts("\n");
    printf("o(N) max sum is %d \n", res_N);
    res_N2 = cal_seq_num_N2(array, size);
    printf("o(N2) max sum is %d \n", res_N2);
    return 0;
}


int cal_seq_num_N(int array[], int size){
    int max_sum = 0;
    int this_max = 0;
    for(int i=0; i < size; i++){
        max_sum += array[i];
        if(max_sum > this_max){
            this_max = max_sum;
        }
        if(max_sum < 0){
            max_sum = 0;
        }
    }
    return this_max;
}

int cal_seq_num_N2(int array[], int size){
    int max_sum=0, this_sum = 0;
    for(int i=0; i < size; i++){
        max_sum = 0;
        for(int j=i; j < size; j++){
            max_sum += array[j];
            if(max_sum > this_sum){
                this_sum = max_sum;
            }
        }
    }
    return this_sum;
}

void show_array(int ar[], int size){
    for(int i=0; i < size; i++){
        printf("%d ", ar[i]);
    }
}

void fix_array(int arr[], int size){
    for(int i=0; i < size; i++){
        arr[i] = generate_rand();
    }
}

void input_array(int arr[], int size){
    printf("enter a sequence elements: \n");
    for(int i=0; i < size; i++){
        scanf("%d", &arr[i]);
    }
}

// 生成-500 ～ 500 的随机数
int generate_rand(void){
    return rand()%2001 - 1000;
}