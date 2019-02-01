#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./util/queue.h"

#define VERTICES 5

typedef struct AdjNode{
    int dest;
    struct AdjNode *next;
}AdjNode;

typedef struct AdjList{
    struct AdjNode *head;
}AdjList;

typedef struct Graph{
    int v;  // number of vertices in graph.
    AdjList *array;
}Graph;

Graph* create_graph(int);
void add_edge(Graph*, int, int);
AdjNode* new_Adj_node(int);
void print_graph(Graph*);

void t_DFS(Graph*, int); // 深度优先遍历
void t_BFS(Graph *, int); // 广度优先遍历

void dfs_helper(Graph*, bool[], int);
void bfs_helper(Graph*, bool[], int);

int node_count = 0;
LinkQueue *q;

// undirect Graph Traversal/addEdge. Using Adjacency List
// If modify graph adjcent, must reset VERTICES
int main(int argc, char const *argv[])
{
    Graph *graph = create_graph(VERTICES);
    q = create_queue(q);

    // add_edge(graph, 0, 1);
    // add_edge(graph, 0, 2);
    // add_edge(graph, 1, 2);
    // add_edge(graph, 2, 3);
    // add_edge(graph, 3, 4);
    // add_edge(graph, 4, 5);
    // add_edge(graph, 1, 5);
    // add_edge(graph, 4, 6);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 4);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 3, 4);

    print_graph(graph);
    t_DFS(graph, 1);
    t_BFS(graph, 1);
    return 0;
}

// 深度优先搜索  应用递归和栈来处理
// @param g graph v: 节点所在序号
void t_DFS(Graph* g, int v){
    bool marked[VERTICES];
    for(int i=0; i < VERTICES; i++)
        marked[i] = false;
    puts("DFS Traversal: \n");
    for(int j=0; j < VERTICES; j++)
        if(!marked[j])
            dfs_helper(g, marked, j);
    puts("");
}

void dfs_helper(Graph* g, bool marked[], int v){
    AdjNode *n = g->array[v].head;
    marked[n->dest] = true;
    int w;
    printf("->%d ", n->dest);

    for(; n; n=n->next){
        if(!marked[n->dest]){
            dfs_helper(g, marked, n->dest);
        }
    }
}

// 广度优先搜索  应用队列来处理
// @param g graph v: 节点所在序号
void t_BFS(Graph *g, int v){
    bool marked[VERTICES];
    for(int i=0; i < VERTICES; i++)
        marked[i] = false;
    puts("BFS Traversal: \n");
    bfs_helper(g, marked, 0);
    puts("");
}

void bfs_helper(Graph *g, bool marked[], int v){
    AdjNode *node, *data;
    for(int i = 0; i < g->v; i++){
        if (!marked[i]) {

            marked[i] = true;
            addQ(q, g->array[i].head);
            while(!isEmptyQ(q)){
                data = delQ(q);
                printf("->%d ", data->dest);
                // 1. 寻找节点
                for(int j=0; j < g->v; j++){
                    if(g->array[j].head->dest == data->dest){
                        node = g->array[j].head;
                    }
                }

                // 2. 循环节点的链
                while(node){
                    if(!marked[node->dest]){
                        marked[node->dest] = true;
                        addQ(q, node);
                    }
                    node = node->next;
                }
            }
        }
        
    }
}

Graph* create_graph(int V){
    Graph *g = (Graph*) malloc(sizeof(Graph));
    g->v = V;

    g->array = (AdjList*) malloc(V * sizeof(AdjList));
    for(int i=0; i < V; i++){
        g->array[i].head = NULL;
    }

    return g;
}

AdjNode* new_Adj_node(int dest){
    AdjNode *node = (AdjNode*) malloc(sizeof(AdjNode));
    node->dest = dest;
    node->next = NULL;
    return node;
}

void add_edge(Graph* g, int src, int dest){
    // 保证头节点有值
    if (g->array[src].head == NULL) {
        g->array[src].head = new_Adj_node(src);
    }
    if (g->array[dest].head == NULL) {
        g->array[dest].head = new_Adj_node(dest);
    }
    // 1. 给src指向dest
    AdjNode* new_node = new_Adj_node(dest);
    AdjNode *s_n = g->array[src].head;
    while(s_n){
        if (s_n->next == NULL){
            s_n->next = new_node;
            break;
        }
        s_n = s_n->next;
    }
    
    // 2. 无向图，因此让dest指向src
    new_node = new_Adj_node(src);
    AdjNode *d_n = g->array[dest].head;
    while(d_n){
        if(d_n->next == NULL){
            d_n->next = new_node;
            break;
        }
        d_n = d_n->next;
    }

    // AdjNode* new_node = new_Adj_node(dest);
    // new_node->next = g->array[src].head;
    // g->array[src].head = new_node;

    // // Since graph is undirect graph, add an edge from src to dest.
    // new_node = new_Adj_node(src);
    // new_node->next = g->array[dest].head;
    // g->array[dest].head = new_node;
}

void print_graph(Graph* g){

    for(int i=0; i < g->v; i++){
        printf("vertice is %d head", i);
        AdjNode *n = g->array[i].head;
        while(n){
            printf("->%d ", n->dest);
            n = n->next;
        }
        puts("");
    }
}