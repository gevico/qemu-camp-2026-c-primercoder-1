#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int vis[MAX_ROW][MAX_COL] = {0};
int pre[MAX_ROW][MAX_COL];
struct node {
	int i;
	int j;
	struct node *next;
};
void push(struct node *p, struct node *n)
{
	n->next = p->next;
	p->next = n;
}
struct node *pop(struct node *p)
{
	struct node *res = p->next;
	p->next = res->next;
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

int main(void)
{
	// TODO: 在这里添加你的代码
    struct node h;
	h.next = NULL;
	struct node *n = (struct node *)malloc(sizeof(struct node));
	n->i = 0, n->j = 0, n->next = NULL;
	push(&h, n);
	while(qsize(&h)) {
		int curn = qsize(&h);
		for(int i=0;i<curn;i++) {
			struct node *p = pop(&h);
			vis[p->i][p->j] = 1;
			if(p->i-1>=0 && !vis[p->i-1][p->j] && !maze[p->i-1][p->j]) {
				n = (struct node *)malloc(sizeof(struct node));
				n->i = p->i-1, n->j = p->j, n->next = NULL;
				push(&h, n);
				pre[p->i-1][p->j] = p->i * MAX_ROW + p->j;
			}
			if(p->i+1<MAX_ROW && !vis[p->i+1][p->j] && !maze[p->i+1][p->j]) {
				n = (struct node *)malloc(sizeof(struct node));
				n->i = p->i+1, n->j = p->j, n->next = NULL;
				push(&h, n);
				pre[p->i+1][p->j] = p->i * MAX_ROW + p->j;
			}
			if(p->j-1>=0 && !vis[p->i][p->j-1] && !maze[p->i][p->j-1]) {
				n = (struct node *)malloc(sizeof(struct node));
				n->i = p->i, n->j = p->j-1, n->next = NULL;
				push(&h, n);
				pre[p->i][p->j-1] = p->i * MAX_ROW + p->j;
			}
			if(p->j+1<MAX_COL && !vis[p->i][p->j+1] && !maze[p->i][p->j+1]) {
				n = (struct node *)malloc(sizeof(struct node));
				n->i = p->i, n->j = p->j+1, n->next = NULL;
				push(&h, n);
				pre[p->i][p->j+1] = p->i * MAX_ROW + p->j;
			}
		}
	}
	int x = MAX_ROW-1, y = MAX_COL-1;
	while(!(x==0 && y==0)) {
		printf("(%d, %d)\n", x, y);
		int idx = pre[x][y];
		x = idx / MAX_COL;
		y = idx % MAX_COL;
	}
	printf("(%d, %d)\n", x, y);
	return 0;
}