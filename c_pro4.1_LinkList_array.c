#include <stdio.h>

#define MAXSIZE 255

typedef struct List{
    int data[MAXSIZE]; // 对应的元素值
    int last; // 线性表的最后一个元素的位置。0表示只有一个元素且放在第一个位置，没有元素则为-1
}List;

List *initList(); // 初始化空表
void insert(int, int, List*); // 在point位置插入value
void delete(int, List*); // 将point位置的元素删除
int find(int, List*); //根据point位置查找
int length(List*); // 返回链表的长度

/*
* 顺序表的顺序结构（数组）实现形式
*/
int main(int argc, char const *argv[])
{
    int size = 0;
    List *list = initList();
    printf("输入链表的长度：");
    scanf("%d", &size);
    printf("输入链表的元素");
    int val = 1;
    printf("size is %d \n", size);
    for(int t=1; t <= size; t++){
        scanf("%d", &val);
        insert(val, t, list);
    }
    printf("输入你要查找的元素数： \n");
    int findX;
    scanf("%d", &findX);
    printf("%d 在第 %d 个位置\n", findX, find(findX, list));

    printf("输入你要删除的元素：\n");
    scanf("%d", &findX);
    delete(findX, list);
    for(int j=0; j <= length(list); j++){
        printf("linkList element is %d \n", list->data[j]);
    }
    return 0;
}

List *initList(){
    List *ptr;
    ptr = (List *) malloc(sizeof(List));
    ptr->last = -1;
    return ptr;
}

// 将value值插入到list中的point位置
void insert(int value, int point, List *ptr){
    // 插入位置合法性检查
    if(point < 1 || point > MAXSIZE+1)
        printf("插入位置错误..\n");
    if(ptr->last == MAXSIZE-1){
        printf("线性表已满，无法插入..\n");
    }
    for(int i = ptr->last; i > point-1; i--){
        ptr->data[i+1] = ptr->data[i]; // 把插入位置后面的元素全部往后挪动一个位置，注意是从后往前挪。
    }
    ptr->data[point-1] = value;
    ptr->last++;
    return;
}

// 根据元素位置删除元素
void delete(int point, List *ptr){
    // 删除位置合法性检查
    if(point < 1 || point > length(ptr)){
        printf("删除位置错误..\n");
        return;
    }
    for(int i = point; i <= ptr->last; i++){
        ptr->data[i-1] = ptr->data[i]; // 把插入位置后面的元素全部往后挪动一个位置，注意是从前往后挪。
    }
    ptr->last--;
    return;
}

// 查找x元素所在位置
int find(int x, List *ptr){
    int i=0;
    while(i <= ptr->last && ptr->data[i] != x)
        i++;
    if(i > ptr->last) return -1; // 表示没有查找到
    return i+1;
}

int length(List *ptr){
    return ptr->last;
}
