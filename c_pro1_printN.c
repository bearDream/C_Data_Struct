#include <stdio.h>
#include <time.h>

void recursive_print(int);
void foreach_print(int);

clock_t start_time, end_time;

// 递归和for循环调用将该数的分解打印Polynominal
int main(int argc, char const *argv[])
{
    int number = 100000;
    double recursive_time, foreach_time;
    
    printf("----recursice print start--- \n");
    start_time = clock();
    recursive_print(number);
    end_time = clock();
    printf("----recursice print end--- \n");
    recursive_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("----recursice print time: %f--- \n", recursive_time);

    printf("----foreach print start--- \n");
    start_time = clock();
    foreach_print(number);
    end_time = clock();
    printf("----foreach print end--- \n");
    recursive_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("----recursice print time: %f--- \n", recursive_time);
    printf("----foreach print time: %f--- \n", foreach_time);
    return 0;
}

// 递归调用打印
void recursive_print(int num){
    if(num == 0){
        return;
    }
    printf("%d ", num);
    recursive_print(num - 1);
}

void foreach_print(int num){
    for(int i = 0; i < num; i++){
        printf("%d ", i);
    }
}