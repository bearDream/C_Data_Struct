#include <stdbool.h>
#include "./util/util.h"

// 河岸的X，Y坐标 （X= +-BORDERX; Y= +-BORDERY）
#define BORDERX 15
#define BORDERY 15
#define DISTANCE 5 // 007可跳动的最大距离 最大为2个格子的距离
#define CROCODILE 20 // 鳄鱼数量

typedef struct Node{
    int x; // x轴坐标
    int y; // y轴坐标
}Node;

typedef struct lake{
    Node *head;
}lake;

lake *init_lake(Node[]);
void find_route(Node *, lake *);
void find_helper(Node *);
bool is_center(Node*);
bool first_jump(Node*); // 判断是不是处于第一跳以及是否可以跳
bool can_jump(Node *, Node *); // 给出007当前所在节点，判断其是否可以跳到下一个鳄鱼头
bool DFS(Node*, bool marked[][CROCODILE], lake*); // DFS递归寻路，若返回true则表明可以上岸
bool is_safe(Node*); // 判断当前节点是否可以直接上岸，若可以上岸则007可以逃脱

// 测试二维数组传参
void test(bool m[][CROCODILE], int i){
    for(int i = 0; i < CROCODILE; i++){
        for(int j = 0; j < CROCODILE; j++){
            printf("mark[%d][%d]: %d", i, j, m[i][j]);
        }
        printf("new line----\n");    
    }
}

void para(){
    bool marked[CROCODILE][CROCODILE];
    for(int i = 0; i < CROCODILE; i++){
        for(int j = 0; j < CROCODILE; j++){
            marked[i][j] = false;
        }
    }
    marked[0][1] = true;
    test(marked, 1);
}

/*
 *  拯救007.
 *  007所处于一个湖心岛中，湖中有若干鳄鱼，007需要跳在鳄鱼头上并最终上岸
 *  问题抽象为：从坐标轴原点出发，找到一条可以上岸的路径，只有当两点之间距离小于等于3个坐标单位时才可移动 
 */
int main(int argc, char const *argv[]){
    Node n[CROCODILE+1];
    lake *g = init_lake(n);
    para(); // test func
    find_route(n, g);
    return 0;
}

lake *init_lake(Node n[]){
    // 007的初始位置位于湖心岛中, 即坐标为(0, 0)
    n[0].x = 0;
    n[0].y = 0;
    // 随机生成鳄鱼的位置信息, 确保每个坐标点只有一条鳄鱼
    srand((unsigned)time(NULL));
    for(int i = 1; i < CROCODILE; i++){
        n[i].x = get_rand(1, 15);
        n[i].y = get_rand(1, 15);
    }
    lake *g = (lake *) malloc(sizeof(lake));
    g->head = n;
    return g;
}

void find_route(Node *g, lake *head){
    bool answer = false;
    // 1. 初始化标记数组
    bool marked[CROCODILE][CROCODILE];
    for(int i = 0; i < CROCODILE; i++){
        for(int j = 0; j < CROCODILE; j++){
            marked[i][j] = false;
        }
    }
    
    // 2. 找路
    for(int i=0; i < CROCODILE; i++, g++){
        // printf("crocodiles: %d  %d \n", g->x, g->y);

        if (!marked[g->x][g->y] && first_jump(g)) {
            answer = DFS(g, marked, head);
            if (answer) break;
        }
    }
    if (answer) printf("007 was saved!..\n");
    else printf("007 was dead!..GAME\n");
}

bool DFS(Node *node, bool marked[][CROCODILE], lake *g){
    bool answer = false;
    marked[node->x][node->y] = true;
    if (is_safe(node)) return true;
    else{
        Node *temp;
        temp = g->head;
        for(int i=0; i < CROCODILE; i++, temp++){
            if (!marked[node->x][node->y] && can_jump(node, temp)) {
                answer = DFS(temp, marked, g);
                if (answer) break;
            }
        }
    }
    return answer;
}

bool first_jump(Node *node){
    bool res = false;
    Node *temp = node;
    temp++;
    if (is_center(node)) {
        for(int i = 1; i < CROCODILE; i++, temp++){
            if (can_jump(node, temp)) {
                printf("[DEBUG]: first crocodile locate in --%d--%d--\n", temp->x, temp->y);
                return true;
            }
        }
    }
    return false;
}

bool is_safe(Node *node){
    if ((BORDERX - node->x <= DISTANCE)
            && (BORDERY - node->y <= DISTANCE))
        return true;
    return false;
}

bool can_jump(Node * cur, Node *other){
    printf("cur: %d--%d;  other: %d---%d\n", cur->x, cur->y, other->x, other->y);
    // 用other的坐标减去cur的坐标，若满足  -DISTANCE< other-cur <DISTANCE 则表示满足
    if (((other->x - cur->x <= DISTANCE) && (other->x - cur->x >= -DISTANCE)) 
            && ((other->y - cur->y <= DISTANCE) && (other->y - cur->y >= -DISTANCE))) 
        return true;
    else
        return false;
}

bool is_center(Node *node){
    if (node->x == 0 && node->y == 0) return true;
    else return false;
}


void find_help(Node *node){
    // bool is_way = false; // 指明接下来是否有鳄鱼头或岸边可以逃走
    // // 1. 从湖心找第一个节点
    // if (is_center(*g)) {
    //     if () {
    //         /* code */
    //     }
        
    //     printf("%d--%d 是湖心\n", g->x, g->y);
    //     g++;
    //     find_route(g);
    // }else{
    //     printf("%d--%d 不是湖心\n", g->x, g->y);
    // }
    
    // 2. 递归找寻半径内是否还有节点，若没有则返回false，否则返回true
}