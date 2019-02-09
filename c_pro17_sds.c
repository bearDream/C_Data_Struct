#include <stdbool.h>
#include "./util/util.h"
#include "./util/queue.h"

#define PEOPLE 10

typedef struct Node{
    int id; // 该用户的唯一标识符
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

LinkQueue *q;

NetWork *initNetwork();
void SDS(NetWork *);
int SDS_helper(Node *, NetWork *); // 将要查找的用户id传过去进行查找
int BFS(Node *);

char *search_name(int, NetWork *, char *);
void print_network(NetWork *);
Node* new_node(char [], int);

/*
 *  六度空间理论(BFS应用) 的验证
 *  在一个社交网络中，同学A寻找另外一个人仅需要小于等于6个人即可找到, 计算在一个随机网络中满足SDS理论的人数占比
 *  抽象为： 在一个图中，一个节点寻找另外一个节点仅需要广度优先遍历至多6层即可找到。
 */
int main(int argc, char const *argv[]){
    NetWork *g = initNetwork();
    q = create_queue(q);
    print_network(g);

    SDS(g);
    return 0;
}

void SDS(NetWork *g){
    bool proportion[PEOPLE];
    int count = 0;
    // 1. 对每个人都尝试用六度空间寻找
    for(int i = 0; i < PEOPLE; i++){
        Node *node = g->Array[i].head;
        int c = SDS_helper(node, g);
        printf("count：%d  people %d\n", c, PEOPLE);
    }
}

// 对一个用户尝试广度优先遍历6层, 返回访问过多少人的数量
int SDS_helper(Node *node, NetWork *g){
    bool marked[PEOPLE];
    for(int i = 0; i < PEOPLE; i++)
        marked[i] = false;
    
    Node *tail;
    int level = 0; // 层数
    int count = 1; // 访问的节点数
    Node *last = node; // 指示一层中最后一个元素
    marked[node->id] = true;
    addQ(q, node);
    while(!isEmptyQ(q)){
        node = delQ(q);
        printf("delQ: %s ", node->data);

        // 寻找该节点的关系网络是否有目标
        while(node){
            if (!marked[node->id]) {
                marked[node->id] = true;
                addQ(q, node);
                count++;
                tail = node;
            }
            if (node->id == last->id) {
                level++;
                last = tail;
            }
            
            if (level == 6) break;    
            
            node = node->next;
        }
    }
    return count;
}

char *search_name(int id, NetWork *g, char *target){
    Node *t_head;
    for(int i = 0; i < g->v; i++){
        t_head = g->Array[i].head;
        if (t_head->id == id) {
            strcpy(target, t_head->data);
            return target;
        }
    }
    return NULL;
    
}

Node* new_node(char data[], int id){
    Node *node = (Node*) malloc(sizeof(Node));
    strcpy(node->data, data);
    node->id = id;
    node->next = NULL;
    return node;
}

void print_network(NetWork *g){
    for(int i = 0; i < g->v; i++){
        Node *node = g->Array[i].head;
        printf("%s 的关系网有", node->data);
        while(node != NULL){
            printf("->%s ", node->data);
            node = node->next;
        }
        printf("\n");
    }
}

NetWork *initNetwork(){
    NetWork *g = (NetWork *)malloc(sizeof(NetWork));
    g->Array = (NodeList *) malloc(PEOPLE * sizeof(NodeList));
    g->v = PEOPLE;
    // 指定节点
    g->Array[0].head = new_node("A", 0);
    g->Array[1].head = new_node("B", 1);
    g->Array[2].head = new_node("C", 2);
    g->Array[3].head = new_node("D", 3);
    g->Array[4].head = new_node("E", 4);
    g->Array[5].head = new_node("F", 5);
    g->Array[6].head = new_node("G", 6);
    g->Array[7].head = new_node("H", 7);
    g->Array[8].head = new_node("I", 8);
    g->Array[9].head = new_node("J", 9);

    // 设置关系网
    // A->C->B->J
    Node *node_A = g->Array[0].head;
    node_A->next = new_node(g->Array[2].head->data, g->Array[2].head->id);
    node_A->next->next = new_node(g->Array[1].head->data, g->Array[1].head->id);
    node_A->next->next->next = new_node(g->Array[9].head->data, g->Array[9].head->id);
    node_A->next->next->next->next = NULL;

    // B->A->D->E->F
    Node *node_B = g->Array[1].head;
    node_B->next = new_node(g->Array[0].head->data, g->Array[0].head->id);
    node_B->next->next = new_node(g->Array[3].head->data, g->Array[3].head->id);
    node_B->next->next->next = new_node(g->Array[4].head->data, g->Array[4].head->id);
    node_B->next->next->next->next = new_node(g->Array[5].head->data, g->Array[5].head->id);
    node_B->next->next->next->next->next = NULL;

    // C->A->G
    Node *node_C = g->Array[2].head;
    node_C->next = new_node(g->Array[0].head->data, g->Array[0].head->id);
    node_C->next->next = new_node(g->Array[6].head->data, g->Array[6].head->id);
    node_C->next->next->next = NULL;

    // D B I H
    Node *node_D = g->Array[3].head;
    node_D->next = new_node(g->Array[1].head->data, g->Array[1].head->id);
    node_D->next->next = new_node(g->Array[8].head->data, g->Array[8].head->id);
    node_D->next->next->next = new_node(g->Array[7].head->data, g->Array[7].head->id);
    node_D->next->next->next->next = NULL;

    // E B F G
    Node *node_E = g->Array[4].head;
    node_E->next = new_node(g->Array[1].head->data, g->Array[1].head->id);
    node_E->next->next = new_node(g->Array[5].head->data, g->Array[5].head->id);
    node_E->next->next->next = new_node(g->Array[6].head->data, g->Array[6].head->id);
    node_E->next->next->next->next = NULL;

    // F B
    Node *node_F = g->Array[5].head;
    node_F->next = new_node(g->Array[1].head->data, g->Array[1].head->id);
    node_F->next->next = NULL;

    // G C E
    Node *node_G = g->Array[6].head;
    node_G->next = new_node(g->Array[2].head->data, g->Array[2].head->id);
    node_G->next->next = new_node(g->Array[4].head->data, g->Array[4].head->id);
    node_G->next->next->next = NULL;

    // H I D
    Node *node_H = g->Array[7].head;
    node_H->next = new_node(g->Array[8].head->data, g->Array[8].head->id);
    node_H->next->next = new_node(g->Array[3].head->data, g->Array[3].head->id);
    node_H->next->next->next = NULL;

    // I D H
    Node *node_I = g->Array[8].head;
    node_I->next = new_node(g->Array[3].head->data, g->Array[3].head->id);
    node_I->next->next = new_node(g->Array[7].head->data, g->Array[7].head->id);
    node_I->next->next->next = NULL;

    // J A
    Node *node_J = g->Array[9].head;
    node_J->next = new_node(g->Array[0].head->data, g->Array[0].head->id);
    node_J->next->next = NULL;

    // // K J
    // Node *node_K = g->Array[10].head;
    // node_K->next = new_node(g->Array[9].head->data, g->Array[9].head->id);
    // node_K->next->next = NULL;

    // // L J
    // Node *node_L = g->Array[11].head;
    // node_L->next = g->Array[9].head;
    // node_L->next->next = NULL;

    return g;
}

/*
// 初始化一个网络, 随机生成的关系网算法不正确，此种生成的关系网是矛盾的
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
        g->Array[i].head = new_node(s[count].string, i);

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
*/