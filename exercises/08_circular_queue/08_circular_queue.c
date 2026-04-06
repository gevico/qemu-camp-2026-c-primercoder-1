#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

struct node {
	int id;
	struct node *next;
};
void push(struct node *p, struct node *n)
{
    while(p->next) p = p->next;
	p->next = n;
}
struct node *pop(struct node *p)
{
	struct node *res = p->next;
	p->next = res->next;
    res->next = NULL;
	return res;
}
int qsize(struct node *p)
{
	struct node *t = p->next;
	int res = 0;
	while(t) {
		res++;
		t = t->next;
	}
	return res;
}

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    struct node h, *t;
    t = &h;
    for(int i=1;i<=MAX_PEOPLE;i++) {
        struct node *p = (struct node *)malloc(sizeof(struct node));
        p->id = i;
        p->next = NULL;
        t->next = p;
        t = p;
    }
    int idx = 1;
    while(qsize(&h)>1) {
        struct node *p = pop(&h);
        if(idx % report_interval != 0) {
            push(&h, p);
            idx++;
        } else {
            printf("淘汰: %d\n", p->id);
            idx = 1;
        }
    }
    printf("最后剩下的人是: %d\n", h.next->id);
    return 0;
}