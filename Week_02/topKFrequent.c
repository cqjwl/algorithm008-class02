#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "uthash.h"
#include "topKFrequent.h"

typedef struct hash_entry {
    int key;
    int cnt;
    UT_hash_handle hh;
} entry;

entry* FindHash(entry** hashMap, int k){
    entry* ret = NULL;
    HASH_FIND_INT(*hashMap, &k, ret);
    return ret;
}

bool AddHash(entry** hashMap, int k){
    entry* ret = NULL;
    HASH_FIND_INT(*hashMap, &k, ret);
    if (ret == NULL) {
        entry* p = (entry*)malloc(sizeof(entry));
        p->key = k;
        p->cnt = 1;
        HASH_ADD_INT(*hashMap, key, p);
        return true;
    } else {
        ret->cnt++;
        return true;
    }     
}

void FreeHash(entry** hashMap){  
    entry *current_entry, *tmp;  
    HASH_ITER(hh, *hashMap, current_entry, tmp) {  
        HASH_DEL(*hashMap,current_entry);    
        free(current_entry);              
    }  
}

int cmp(entry* a, entry* b){
    if (b->cnt > a->cnt) {
        return 1;
    }
    return -1;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    returnSize[0] = 0;
    if (nums == NULL || numsSize <= 0 || k > numsSize) {
        return NULL;
    }
    
    entry* hashMap = NULL;
    for (int i = 0; i < numsSize; i++) {
        AddHash(&hashMap, nums[i]);
    }

    int *result = (int*)malloc(sizeof(int) * (k + 1));
    returnSize[0] = k;

    HASH_SORT(hashMap, cmp);
    entry* tmp;
    int i = 0;
    for (tmp = hashMap; tmp != NULL; tmp = tmp->hh.next) {
        result[i++] = tmp->key;
        if (i == k) {
            break;
        }
    }
    FreeHash(&hashMap);

    return result;
}
