#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    // TODO: 在这里添加你的代码
    QueueNode *p = (QueueNode *)malloc(sizeof(QueueNode));
    p->tree_node = tree_node;
    p->next = NULL;
    if(!q->front) {
        q->front = q->rear = p;
    } else {
        q->rear->next = p;
        q->rear = p;
    }
}

TreeNode* dequeue(Queue *q) {
    // TODO: 在这里添加你的代码
    QueueNode *cur = q->front;
    if(q->front==q->rear) {
        q->front = q->rear = NULL;
    } else {
        q->front = q->front->next;
    }
    return cur->tree_node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    // TODO: 在这里添加你的代码
    if(size==0) return NULL;
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = level_order[0];
    root->left = root->right = NULL;
    int num = 1, curidx = 1;
    Queue *q = create_queue();
    enqueue(q, root);
    while(!is_empty(q)) {
        int n = 0;
        TreeNode *cur;
        for(int i=0;i<num;i++) {
            cur = dequeue(q);
            if(curidx<size && level_order[curidx]!=INT_MIN) {
                TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
                p->val = level_order[curidx];
                p->left = p->right = NULL;
                cur->left = p;
                enqueue(q, p);
                n++;
            }
            curidx++;
            if(curidx<size && level_order[curidx]!=INT_MIN) {
                TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
                p->val = level_order[curidx];
                p->left = p->right = NULL;
                cur->right = p;
                enqueue(q, p);
                n++;
            }
            curidx++;
        }
        num = n;
    }
    return root;
}

void preorder_traversal(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if(!root) return;
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    // TODO: 在这里添加你的代码
    Queue *q1 = create_queue(), *q2 = create_queue();
    enqueue(q1, root);
    while(!is_empty(q1)) {
        while(q1->front!=q1->rear) {
            enqueue(q2, dequeue(q1));
        }
        TreeNode *cur = dequeue(q1);
        while(q2->front!=NULL) enqueue(q1, dequeue(q2));
        printf("%d ", cur->val);
        if(cur->right) enqueue(q1, cur->right);
        if(cur->left) enqueue(q1, cur->left);
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
