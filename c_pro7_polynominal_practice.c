#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct PolyNode{
    int coef;  //系数
    int expon; // 指数
    struct PolyNode *next;
}PolyNode;

PolyNode *build_Polynominal_1(PolyNode *);
PolyNode *build_Polynominal_2(PolyNode *);
PolyNode *create_node(void);
void printNode(PolyNode*);
PolyNode *poly_add(PolyNode *, PolyNode *);
int compare_poly(int, int);
PolyNode *attach(int, int, PolyNode *);

// P1: 5X^4 + 3X^2 + 2X
// P2: 6X^6 + 5X^4 + 3X^2 + X
int main(int argc, char const *argv[])
{
    PolyNode *p1, *p2;
    p1 = build_Polynominal_1(p1);
    p2 = build_Polynominal_2(p2);
    // printNode(p1);
    // printNode(p2);
    PolyNode *res = poly_add(p1, p2);
    printNode(res);
    return 0;
}

// 两多项式相加
PolyNode *poly_add(PolyNode *p1, PolyNode *p2){
    PolyNode *front, *rear;
    rear = create_node(); // 合并后的多项式首节点
    front = rear;
    int sum=0;
    puts("ready to add..");
    // 两个多项式都还有项时才可相加
    while(p1 && p2){
        switch(compare_poly(p1->expon, p2->expon)){
            case 1:
                rear = attach(p1->coef, p1->expon, rear);
                p1 = p1->next;
                break;
            case -1:
                rear = attach(p2->coef, p2->expon, rear);
                p2 = p2->next;
                break;
            case 0:
                // 将两项相加
                sum = (p1->coef) + (p2->coef);
                if(sum == 0) {
                    p1 = p1->next;
                    p2 = p2->next;
                    break;
                }
                rear = attach(sum, p1->expon, rear);
                p1 = p1->next;
                p2 = p2->next;
                break;
            default:break;
        }
    }
    puts("end to add..");
    for(;p1; p1 = p1->next) attach(p1->coef, p1->expon, rear);
    for(;p2; p2 = p2->next) attach(p2->coef, p2->expon, rear);

    rear->next = NULL;
    front = front->next;
    return front;
}

// 比较两个节点的指数
int compare_poly(int p1_expon, int p2_expon){
    if(p1_expon > p2_expon)
        return 1;
    else if(p1_expon < p2_expon)
        return -1;
    else
        return 0;
}

PolyNode *attach(int coef, int expon, PolyNode *rear){
    PolyNode *new_node = create_node();
    new_node->coef = coef;
    new_node->expon = expon;
    rear->next = new_node;
    rear = new_node;
    return rear;
}


PolyNode *create_node(){
    PolyNode *node = (PolyNode *) malloc(sizeof(PolyNode));
    if(node == NULL){
        perror("create node");
        exit(-1);
    }
    return node;
}

PolyNode *build_Polynominal_1(PolyNode *p1){
    // build p1
    p1 = create_node();

    PolyNode *p1_2 = create_node();
    PolyNode *p1_3 = create_node();
    PolyNode *p1_4 = create_node();
    PolyNode *p1_5 = create_node();
    p1->coef = 3;
    p1->expon = 5;
    p1_2->coef = 4;
    p1_2->expon = 4;
    p1_3->coef = -1;
    p1_3->expon = 3;

    p1_4->coef = 2;
    p1_4->expon = 1;
    p1_5->coef = -1;
    p1_5->expon = 0;

    p1->next = p1_2;
    p1_2->next = p1_3;
    p1_3->next = p1_4;
    p1_4->next = p1_5;
    p1_5->next = NULL;
    return p1;

}

PolyNode *build_Polynominal_2(PolyNode *p2){
    p2 = create_node();
    // build p2
    PolyNode *p2_2 = create_node();
    PolyNode *p2_3 = create_node();
    PolyNode *p2_4 = create_node();
    p2->coef = 2;
    p2->expon = 4;
    p2_2->coef = 1;
    p2_2->expon = 3;
    p2_3->coef = -7;
    p2_3->expon = 2;
    p2_4->coef = 1;
    p2_4->expon = 1;
    p2->next = p2_2;
    p2_2->next = p2_3;
    p2_3->next = p2_4;
    p2_4->next = NULL;
    return p2;
}

void printNode(PolyNode *node){
    printf("多项式为：\n");
    while(node != NULL){
        printf("coef: %d, expon: %d \n", node->coef, node->expon);
        node = node->next;
    }
}