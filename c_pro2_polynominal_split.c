#include <stdio.h>
#include <math.h>

#define MAX 10
// int: 多项式有n-1项  double[]多项式每一项的系数 double给定的x值
double cal_1(int, double[], double);
double cal_2(int, double[], double);

// 计算多项式的值 
int main(int argc, char const *argv[])
{
    double a[MAX];
    for(int i=0; i <= MAX; i++)
        a[i] = (double)i;

    printf("%f\n", cal_1(MAX, a, 1.2));
    printf("%f\n", cal_2(MAX, a, 1.2));
    return 0;
}

// 多项式的每一项相加
double cal_1(int n, double a[], double x){
    int i;
    double p = a[0];
    for(i = 0; i <= n; i++){
        p += (a[i] * pow(x, i));
    }
    return p;
}

// 把x不断的提出来，构建成一个洋葱式的结构，从最里面一层一层往外加
double cal_2(int n, double a[], double x){
    int i;
    double p = a[0];
    for(i = n; i > 0; i--){
        p += (a[i - 1] + x*p);
    }
    return p;
}
