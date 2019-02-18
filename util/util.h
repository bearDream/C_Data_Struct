#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct str{
    char string[255];
}str;

// 返回一个在[x, y]范围内的随机数 闭闭区间
int get_rand(int, int);
// 读一根文件的n行，返回字符串数组
str *read_file(FILE *, str[], int);

#endif