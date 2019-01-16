#include <stdio.h>
#include <stdlib.h>

typedef struct LinkList{
    int data;
    struct LinkList *next;
}LinkList;

void push_front(LinkList **, int num); // 插入一个元素在在链表的第一个位置
void append_end(LinkList **, int num); // 追加一个元素在链表最后一个位置
void insert_element(int, LinkList *); // 将元素插入到i-1位置后
LinkList* find_position(int, LinkList *); // 查找元素所在位置
LinkList* find_val(int, LinkList *);  // 查找i位置的元素值
void del_val(LinkList **, int); // 根据val值删除元素
void del_pos(LinkList **, int); // 根据元素索引删除元素
void print_list(LinkList *);
/*
* 顺序表的链式实现形式
*/
int main(int argc, char const *argv[])
{
    LinkList *ptr = NULL;
    append_end(&ptr, 2);
    append_end(&ptr, 1);
    append_end(&ptr, 10);
    push_front(&ptr, 50);
    insert_element(3, ptr->next);
    printf("after add element-----\n");
    print_list(ptr);
    printf("after delete element by value-----\n");
    del_val(&ptr, 2);
    del_val(&ptr, 1);
    append_end(&ptr, 100);
    del_pos(&ptr, 3); // del 100
    print_list(ptr);
    free(ptr); 
    return 0;
}

void push_front(LinkList ** head_ref, int num){
    // 1. allocate node
    LinkList *node = (LinkList*) malloc(sizeof(LinkList));
    // 2. put in the data
    node->data = num;
    // 3. make the new node as head
    node->next = (*head_ref);
    // 4. move the head to point to the new head
    (*head_ref) = node;
}

void append_end(LinkList ** head_ref, int num){
    // 1. allocate node
    LinkList *new_node = (LinkList *) malloc(sizeof(LinkList));
    LinkList * last = *head_ref;
    // 2. put in the data
    new_node->data = num;
    // 3. cause the new node is last one, so make the new node next as null
    new_node->next = NULL;
    // 4. if list is empty, the new node as the first node.
    if((* head_ref) == NULL){
        *head_ref = new_node;
        return;
    }
    // 5. else traverse till the last node
    while(last->next != NULL){
        last = last->next;
    }
    // 6. make the last node point the new node.
    last->next = new_node;
    return;
}

void insert_element(int val, LinkList *prev){
    // 1. check prev whether is null.
    if(prev == NULL){
        perror("前序节点指针为空，无法插入\n");
        return;
    }
    // 2. allocate node.
    LinkList *new_node = (LinkList *) malloc(sizeof(LinkList));
    // 3. put data
    new_node->data = val;
    // 4. make next of new node as next of prev_node
    new_node->next = prev->next;
    // 5. make next of prev_node point the new_node
    prev->next = new_node; 
}

// 根据element查找该元素所在位置
LinkList* find_val(int element, LinkList *list){
    while(list != NULL && list->data != element){
        list = list->next;
    }
    return list;
}

// 根据position查找该元素的值
LinkList* find_position(int position, LinkList *list){

    return list;
}

void del_val(LinkList **head, int val){
    // 1. if del node is front of the list
    LinkList *list = (*head);
    if(list->data == val){
        // 删除第一个节点
        LinkList *front_node = list;
        (*head) = front_node->next;
        free(front_node);
        return;
    }
    // 2. del node not in the first node.
    while(list->next != NULL){
        if(list->next->data == val){
            LinkList *temp = list->next;
            list->next = temp->next;
            free(temp);
            return;
        }else{
            list = list->next;
        }
    }
}

void del_pos(LinkList **list, int pos){
    // 1. check list whether is null
    if(list == NULL){
        perror("list is null. can not delete. \n");
        return;
    }
    // 2. store head node.
    LinkList *temp = *list;
    // 3. if head node needs to be removed
    if(pos == 0){
        *list = temp->next;
        free(temp);
        return;
    }
    // 4. traverse all node find prev node
    int count = 0;
    while(temp){
        if(count == pos-1) break;
        temp = temp->next;
        count++;
    }
    // 5. if prev node is null
    if(temp == NULL){
        perror("the element of list not exist..\n");
        return;
    }
    if(temp->next == NULL){
        printf("%d位置后没有元素了，无法删除.\n", pos);
        return;
    }
    // 6. store next and next of the prev node.
    LinkList *next = temp->next->next;
    // 7. free delete node
    free(temp->next);
    // 8. make the prev node point next node.
    temp->next = next;
}

void print_list(LinkList *head){
    int count = 0;
    while(head != NULL){
        printf("node val is %d\n", head->data);
        head = head->next;
        count++;
    }
    printf("list length is %d \n", count);
}