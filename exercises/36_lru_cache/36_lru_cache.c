#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 16 LRU 缓存淘汰算法（哈希表 + 双向链表）
 *  - put(k,v)、get(k) 均为 O(1)
 *  - 容量满时淘汰最久未使用（LRU）的元素
 */

typedef struct LRUNode {
    int key;
    int value;
    struct LRUNode* prev;
    struct LRUNode* next;
} LRUNode;

typedef struct HashEntry {
    int key;
    LRUNode* node;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    int capacity;
    int size;
    LRUNode* head; /* 最近使用（MRU） */
    LRUNode* tail; /* 最久未使用（LRU） */
    /* 简单链式哈希表 */
    size_t bucket_count;
    HashEntry** buckets;
} LRUCache;

static unsigned hash_int(int key) {
    /* 简单的哈希函数，取模桶数量 */
    return (unsigned)(key * 2654435761u);
}

static HashEntry* hash_find(LRUCache* c, int key, HashEntry*** pprev_next) {
    unsigned idx = hash_int(key) % c->bucket_count;
    HashEntry* entry = c->buckets[idx];
    HashEntry* prev = NULL;
    
    while (entry) {
        if (entry->key == key) {
            if (pprev_next) {
                *pprev_next = prev ? &(prev->next) : &(c->buckets[idx]);
            }
            return entry;
        }
        prev = entry;
        entry = entry->next;
    }
    return NULL;
}

static void list_add_to_head(LRUCache* c, LRUNode* node) {
    if (!c->head) {
        c->head = c->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->next = c->head;
        node->prev = NULL;
        c->head->prev = node;
        c->head = node;
    }
}

static void list_remove(LRUCache* c, LRUNode* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        c->head = node->next;
    }
    
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        c->tail = node->prev;
    }
}

static void list_move_to_head(LRUCache* c, LRUNode* node) {
    if (c->head == node) return;
    list_remove(c, node);
    list_add_to_head(c, node);
}

static LRUNode* list_pop_tail(LRUCache* c) {
    if (!c->tail) return NULL;
    LRUNode* tail = c->tail;
    list_remove(c, tail);
    return tail;
}

/* LRU 接口实现 */
static LRUCache* lru_create(int capacity) {
    LRUCache* c = (LRUCache*)malloc(sizeof(LRUCache));
    if (!c) return NULL;
    
    c->capacity = capacity;
    c->size = 0;
    c->head = c->tail = NULL;
    c->bucket_count = capacity * 2;  /* 桶数量为容量的2倍，减少冲突 */
    c->buckets = (HashEntry**)calloc(c->bucket_count, sizeof(HashEntry*));
    if (!c->buckets) {
        free(c);
        return NULL;
    }
    return c;
}

static void lru_free(LRUCache* c) {
    if (!c) return;
    
    /* 释放所有哈希表项 */
    for (size_t i = 0; i < c->bucket_count; i++) {
        HashEntry* entry = c->buckets[i];
        while (entry) {
            HashEntry* tmp = entry;
            entry = entry->next;
            free(tmp);
        }
    }
    free(c->buckets);
    
    /* 释放所有链表节点 */
    LRUNode* node = c->head;
    while (node) {
        LRUNode* tmp = node;
        node = node->next;
        free(tmp);
    }
    
    free(c);
}

static int lru_get(LRUCache* c, int key, int* out_value) {
    HashEntry* entry = hash_find(c, key, NULL);
    if (!entry) return 0;  /* 未找到 */
    
    /* 移动到链表头部（最近使用） */
    list_move_to_head(c, entry->node);
    *out_value = entry->node->value;
    return 1;
}

static void lru_put(LRUCache* c, int key, int value) {
    HashEntry* entry = hash_find(c, key, NULL);
    
    if (entry) {
        /* key 已存在，更新值并移动到头部 */
        entry->node->value = value;
        list_move_to_head(c, entry->node);
        return;
    }
    
    /* 插入新节点 */
    if (c->size >= c->capacity) {
        /* 容量满，淘汰 tail（最久未使用） */
        LRUNode* to_remove = list_pop_tail(c);
        if (to_remove) {
            /* 从哈希表中删除被淘汰的节点 */
            HashEntry* to_remove_entry = hash_find(c, to_remove->key, NULL);
            if (to_remove_entry) {
                /* 从哈希表链中删除该 entry */
                HashEntry** pprev = NULL;
                hash_find(c, to_remove->key, &pprev);
                if (pprev) {
                    HashEntry* tmp = *pprev;
                    *pprev = tmp->next;
                    free(tmp);
                }
            }
            free(to_remove);
            c->size--;
        }
    }
    
    /* 创建新节点 */
    LRUNode* new_node = (LRUNode*)malloc(sizeof(LRUNode));
    if (!new_node) return;
    new_node->key = key;
    new_node->value = value;
    
    /* 添加到链表头部 */
    list_add_to_head(c, new_node);
    
    /* 添加到哈希表 */
    unsigned idx = hash_int(key) % c->bucket_count;
    HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    if (!new_entry) {
        free(new_node);
        return;
    }
    new_entry->key = key;
    new_entry->node = new_node;
    new_entry->next = c->buckets[idx];
    c->buckets[idx] = new_entry;
    
    c->size++;
}

/* 打印当前缓存内容（从头到尾） */
static void lru_print(LRUCache* c) {
    LRUNode* p = c->head;
    int first = 1;
    while (p) {
        if (!first) printf(", ");
        first = 0;
        printf("%d:%d", p->key, p->value);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    /* 容量 3：put(1,1), put(2,2), put(3,3), put(4,4), get(2), put(5,5) */
    LRUCache* c = lru_create(3);
    if (!c) {
        fprintf(stderr, "创建 LRU 失败\n");
        return 1;
    }

    lru_put(c, 1, 1);
    lru_put(c, 2, 2);
    lru_put(c, 3, 3);
    lru_put(c, 4, 4);

    int val;
    if (lru_get(c, 2, &val)) {
        (void)val;
    }

    lru_put(c, 5, 5);

    lru_print(c);  /* 输出: 5:5, 2:2, 4:4 或 5:5, 4:4, 2:2 (取决于链表实现) */

    lru_free(c);
    return 0;
}