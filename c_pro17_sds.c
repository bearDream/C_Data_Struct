#include <stdbool.h>
#include "./util/util.h"

#define PEOPLE 100

typedef struct Node{
    char data;
    Node *next;
}Node;

typedef struct NodeList{
    Node *head;
}NodeList;

typedef struct NetWork{
    int v;
    NodeList *Array;
}NetWork;

NetWork *initNetwork();
void SDS();
int BFS(Node *);


/*
 *  六度空间理论(BFS应用) 的验证
 *  在一个社交网络中，同学A寻找另外一个人仅需要小于等于6个人即可找到, 计算在一个随机网络中满足SDS理论的人数占比
 *  抽象为： 在一个图中，一个节点寻找另外一个节点仅需要广度优先遍历至多6层即可找到。
 */
int main(int argc, char const *argv[]){
    
    return 0;
}

// 初始化一个网络
NetWork *initNetwork(){
    NetWork *g = (NetWork *)malloc(PEOPLE * sizeof(NetWork));
    for(int i = 0; i < PEOPLE; i++, g++){
        // 给每个人所认识的好友去一个[1, 20]随机数
        g->v = get_rand(1, 20);
        for(int j = 0; j < g->v; j++){
            // 设置一个随机姓名
            // g->Array[j] = ;
        }
        
    }
    
}