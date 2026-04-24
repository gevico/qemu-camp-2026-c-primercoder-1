#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    // TODO: 在这里添加你的代码
    Node *h = NULL, *t;
    for(int i=1;i<=n;i++) {
        Node *p = (Node *)malloc(sizeof(Node));
        p->id = i;
        p->next = NULL;
        if(!h) {
            h = t = p;
        } else {
            t->next = p;
            t = p;
        }
    }
    if(!h) return NULL;
    t->next = h;
    return h;
}

void free_list(Node* head) {
    // TODO: 在这里添加你的代码
    if(!head) return;
    Node *p = head;
    while(1) {
        Node *q = p;
        p = p->next;
        free(q);
        if(p==head) break;
    }
}
