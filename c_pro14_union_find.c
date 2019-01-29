#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10

typedef struct set{
    int data;
    int parent;
}set;

void union_oper(set [], int, int); // union two set.
int find_x(set [], int); // find x from set A
bool is_connect(int, int);
set* build_sets(); // 构建两个树，装到set数组中

// Union-find Set research. 
// can not run!
int main(int argc, char const *argv[])
{
    build_sets(sets);
    printf("%d ", find_x(sets, 4));
    return 0;
}

set* build_sets(set *s){
    s[0].data = -1;
    s[0].parent = -1;
    // 一棵树为6个元素，另一颗有3个元素
    for(int i=1; i <= 9; i++){
        if(i==1){
            s[i].data = 1;
            s[i].parent = -6;
        }
        if(i==7){
            s[i].data = 2;
            s[i].parent = -3;
        }
        if(i < 7) s[i].parent = 1;
        if(i > 7) s[i].parent = 7;
        s[i].data = i;
    }
    return s;
}

int find_x(set s[], int x){
    int i;
    for(i=0; s[i].data!=x && i < MAXSIZE; i++);
    if(i >= MAXSIZE) return -1;// 找不到该元素，返回-1
    for(; s[i].parent > 0; i = s[i].parent);
    return i;
}

void union_oper(set s[], int a, int b){
    int r1, r2;
    r1 = find_x(s, a);
    r2 = find_x(s, b);
    if(r1 < r2)
        s[r1].parent = r2;// r1 和 r2谁更小，谁就是小树，遵循小树并在大树上
    else
        s[r2].parent = r1;
}