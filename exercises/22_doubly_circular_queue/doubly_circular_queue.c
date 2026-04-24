#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    link p = (link)malloc(sizeof(*p));
    if (!p) return NULL;
    p->data = data;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

void free_node(link p) {
    if (!p) return;
    free(p);
}

link search(int key) {
    link cur = head->next;
    while (cur != tail) {
        if (cur->data == key) return cur;
        cur = cur->next;
    }
    return NULL;
}

void insert(link p) {
    if (!p) return;
    // insert after head sentinel
    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
}

void delete(link p) {
    if (!p) return;
    if (p == head || p == tail) return; // do not delete sentinels
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->prev = NULL;
    p->next = NULL;
}

void traverse(void (*visit)(link)) {
    if (!visit) return;
    link cur = head->next;
    while (cur != tail) {
        visit(cur);
        cur = cur->next;
    }
}

void destroy(void) {
    link cur = head->next;
    while (cur != tail) {
        link next = cur->next;
        free_node(cur);
        cur = next;
    }
    head->next = tail;
    tail->prev = head;
}
