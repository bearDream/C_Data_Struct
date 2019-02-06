#include <stdbool.h>
#include "./util/util.h"

#define PEOPLE 100

typedef struct Node{
    char data[20];
    struct Node *next;
}Node;

typedef struct NodeList{
    struct Node *head;
}NodeList;

typedef struct NetWork{
    int v;
    NodeList *Array;
}NetWork;

NetWork *initNetwork();
void SDS();
int BFS(Node *);

Node* new_node(char []);


/*
 *  六度空间理论(BFS应用) 的验证
 *  在一个社交网络中，同学A寻找另外一个人仅需要小于等于6个人即可找到, 计算在一个随机网络中满足SDS理论的人数占比
 *  抽象为： 在一个图中，一个节点寻找另外一个节点仅需要广度优先遍历至多6层即可找到。
 */
int main(int argc, char const *argv[]){
    NetWork *g = initNetwork();
    puts("Init finished.");
    for(int i = 0; i < g->v; i++){
        Node *node = g->Array[i].head;
        printf("%s 的关系网有", node->data);
        while(node != NULL){
            printf("->%s ", node->data);
            node = node->next;
        }
        printf("\n");
    }
    
    return 0;
}

// 初始化一个网络
NetWork *initNetwork(){
    NetWork *g = (NetWork *)malloc(sizeof(NetWork));
    g->Array = (NodeList *) malloc(PEOPLE * sizeof(NodeList));
    g->v = PEOPLE;
    for(int i = 0; i < PEOPLE; i++){
        g->Array[i].head = NULL;
    }
    
    
    str s[100];
    FILE *file = NULL;
    file = fopen("./sample_of_name.txt", "r");
    if (file == NULL) {
        puts("can not open file. check name file.");
        exit(-1);
    }
    read_file(file, s, PEOPLE);
    puts("read_file was finished");
    int cu_people, count = 0; // 取姓名样本的计数器
    Node *node;
    // 设置网络中的人数
    for(int i = 0; i < PEOPLE; i++){
        g->Array[i].head = new_node(s[count].string);
        count++;
    }

    int rand;
    // 设置随机关系网
    for(int j = 0; j < g->v; j++){
        cu_people = get_rand(1, 20);
        Node *node = g->Array[j].head;
        for(int k = 0; k < cu_people; k++){
            rand = get_rand(1, PEOPLE-1);
            node->next = g->Array[rand].head;
            node = node->next;
        }
        node->next = NULL;
    }
    
    return g;    
}

Node* new_node(char data[]){
    Node *node = (Node*) malloc(sizeof(Node));
    strcpy(node->data, data);
    node->next = NULL;
    return node;
}