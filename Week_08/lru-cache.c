#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "lRUCache.h"

typedef struct Node {
    int key;
    int value;
    int time;
    UT_hash_handle hh; 
} NODE_S;

typedef struct {
    NODE_S *head;
    int capacity;
    int time;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));

    cache->capacity = capacity;
    cache->time = INT_MAX;
    cache->head = NULL;
    return cache;
}

NODE_S* lRUCacheFind(LRUCache *obj, int key){
    if (obj->head == NULL) {
        return NULL;
    }

    NODE_S *p = NULL;
    HASH_FIND_INT(obj->head, &key, p);
    if (p == NULL) {
        return NULL;
    }
    return p;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (obj->head == NULL) {
        return -1;
    }

    NODE_S *p = NULL;
    p = lRUCacheFind(obj, key);

    if (p == NULL){
        return -1;
    } 

    obj->time -= 1;
    p->time = obj->time;

    return p->value;
}

void lRUCacheDel(LRUCache* obj)
{
    if (obj->head == NULL) {
        return;
    }

    NODE_S *current = NULL;
    NODE_S *tmp = NULL;
    NODE_S *delNode = NULL;
    int time = INT_MIN;
    HASH_ITER(hh, obj->head, current, tmp) {
        if (delNode == NULL || current->time > delNode->time){
            time = current->time;
            delNode = current;
        }
    }

    if (delNode == NULL) {
        return;
    }
    
    HASH_DEL(obj->head, delNode);
    free(delNode);
    return;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    NODE_S *p = NULL;

    obj->time -= 1;
    p = lRUCacheFind(obj, key);

    if (p != NULL){
        p->value = value;
        p->time = obj->time;
        return;
    } 

    if (obj->capacity == 0) {
        return;
    }

    int num;
    num = HASH_COUNT(obj->head);
    
    if (num >= obj->capacity) {
        lRUCacheDel(obj);
    }

    NODE_S *q = NULL;
    q = malloc(sizeof(NODE_S));
    q->key = key;
    q->value = value;
    q->time = obj->time;
    HASH_ADD_INT(obj->head, key, q); 
    return;
}

void lRUCacheFree(LRUCache* obj) {
    if (obj == NULL) {
        return;
    }

    if (obj->head == NULL) {
        free(obj);
        return;
    }

    NODE_S *current = NULL;
    NODE_S *tmp = NULL;
    HASH_ITER(hh, obj->head, current, tmp)
    {
        HASH_DEL(obj->head, current);
        free(current);
    }
    free(obj);
    return;
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
