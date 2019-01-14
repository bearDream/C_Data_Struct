#include <stdio.h>
#include <time.h>

void do_something();

clock_t start_time, end_time;

int main(int argc, char const *argv[])
{
    double recursive_time, foreach_time;
    // 开始点
    start_time = clock();
    recursive_print();
    // 结束点
    end_time = clock();
    // 计算耗时
    recursive_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("----spend time: %f--- \n", recursive_time);
    return 0;
}

void do_something(){
    // do something...
}