#include <stdbool.h>
#include "./util/util.h"

// 河岸的X，Y坐标 （X= +-BORDERX; Y= +-BORDERY）
#define BORDERX 15
#define BORDERY 15
#define DISTANCE 3 // 007可跳动的最大距离 最大为2个格子的距离
#define CROCODILE 10 // 鳄鱼数量

typedef struct Node{
    int x; // x轴坐标
    int y; // y轴坐标
}Node;

typedef struct lake{
    Node *head;
}lake;

lake *init_lake(Node[]);
void find_route(Node *, lake *);
bool is_center(Node*);
bool first_jump(Node*); // 判断是不是处于第一跳以及是否可以跳
bool can_jump(Node *, Node *); // 给出007当前所在节点，判断其是否可以跳到下一个鳄鱼头
bool DFS(Node*, bool marked[][BORDERY], lake*); // DFS递归寻路，若返回true则表明可以上岸
bool is_safe(Node*); // 判断当前节点是否可以直接上岸，若可以上岸则007可以逃脱

void draw_location(lake *);

/*
 *  拯救007.(DFS的应用问题)
 *  007所处于一个湖心岛中，湖中有若干鳄鱼，007需要跳在鳄鱼头上并最终上岸
 *  问题抽象为：从坐标轴原点出发，找到一条可以上岸的路径，只有当两点之间距离小于等于3个坐标单位时才可移动 
 */
int main(int argc, char const *argv[]){
    Node n[CROCODILE+1];
    lake *g = init_lake(n);
    // draw_location(g);
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
        n[i].x = get_rand(1, BORDERX);
        n[i].y = get_rand(1, BORDERY);
    }
    lake *g = (lake *) malloc(sizeof(lake));
    g->head = n;
    return g;
}

void find_route(Node *g, lake *head){
    bool answer = false;
    // 1. 初始化标记数组
    bool marked[BORDERX][BORDERY];
    for(int i = 0; i < CROCODILE; i++)
        for(int j = 0; j < CROCODILE; j++)
            marked[i][j] = false;
    
    // 2. 对第一个节点用dfs找一遍路
    if (!marked[g->x][g->y] && first_jump(g)) {
        answer = DFS(g, marked, head);
        // if (answer) break;
    }
    if (answer) printf("007 was saved!..MISSION COMPLETE\n");
    else printf("007 was dead!..GAME OVER\n");
}

bool DFS(Node *node, bool marked[][BORDERY], lake *g){
    bool answer = false;
    marked[node->x][node->y] = true;
    if (is_safe(node)) 
        answer = true;
    else{
        Node *temp;
        temp = g->head;
        for(int i=0; i < CROCODILE; i++, temp++){
            // printf("[DEBUG]: marked[%d][%d] is %d\n", temp->x, temp->y, marked[temp->x][temp->y]);
            if (!marked[temp->x][temp->y] && can_jump(node, temp)) {
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
            || (BORDERY - node->y <= DISTANCE))
        return true;
    return false;
}

bool can_jump(Node * cur, Node *other){
    printf("cur: %d--%d;  other: %d---%d", cur->x, cur->y, other->x, other->y);
    // 用other的坐标减去cur的坐标，若满足  -DISTANCE< other-cur <DISTANCE 则表示满足
    if (((other->x - cur->x <= DISTANCE) && (other->x - cur->x >= -DISTANCE)) 
            && ((other->y - cur->y <= DISTANCE) && (other->y - cur->y >= -DISTANCE))){
                printf(" can jump!☑️️️️☑️️️️☑️️️️☑️️️️☑️️️️☑️️️️☑️️️️☑️️️️☑️️️️☑️️️️\n");
                return true;
            } 
    else{
        printf(" can not jump!✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️✖️️️️️\n");
        return false;
    }
}

bool is_center(Node *node){
    if (node->x == 0 && node->y == 0) return true;
    else return false;
}


void draw_location(lake *g){
    for(int i = 0; i < BORDERX*2; i++){
        for(int j = 0; j < BORDERY*2; j++){
            printf(" ");
        }
        printf("+\n");
        if (i==BORDERY) {
            for(int k = 0; k < BORDERY*4; k++){
                printf("+");
            }
        }
        
    }
}