#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    // TODO: 在这里添加你的代码
    link p = (link)malloc(sizeof(struct node));
    p->item = item;
    p->next = NULL;
    return p;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    // TODO: 在这里添加你的代码
    link p = head;
    while(p) {
        if(p->item == key) return p;
        p = p->next;
    }
    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    // TODO: 在这里添加你的代码
    p->next = head;
    head = p;
}

// 删除指定节点
void delete(link p) {
    // TODO: 在这里添加你的代码
    if(head == p) {
        head = head->next;
    } else {
        link q = head;
        while(q->next != p) q = q->next;
        q->next = p->next;
    }
    free_node(p);
}

// 遍历链表
void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    link p = head;
    while(p) {
        visit(p);
        p = p->next;
    }
}

// 销毁整个链表
void destroy(void) {
    // TODO: 在这里添加你的代码
    link p = head;
    while(p) {
        head = head->next;
        free(p);
        p = head;
    }
}

// 在链表头部推入节点
void push(link p) { 
    // TODO: 在这里添加你的代码
    p->next = head;
    head = p;
 }

// 从链表头部弹出节点
link pop(void) {
    // TODO: 在这里添加你的代码
    link p = head;
    head = head->next;
    return p;
}

// 释放链表内存
void free_list(link list_head) {
    // TODO: 在这里添加你的代码
    link p = list_head;
    while(p) {
        list_head = list_head->next;
        free(p);
        p = list_head;
    }
}
