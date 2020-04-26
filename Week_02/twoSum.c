#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "uthash.h"
#include "twoSum.h"

typedef struct hash_entry {
    int key;
    int val[2];
    UT_hash_handle hh;
} entry;

entry* FindHash(entry** hashMap, int k){
    entry* ret = NULL;
    HASH_FIND_INT(*hashMap, &k, ret);
    return ret;
}

bool AddHash(entry** hashMap, int k, int i){
    entry* ret = NULL;
    HASH_FIND_INT(*hashMap, &k, ret);
    if (ret == NULL) {
        entry* p = (entry*)malloc(sizeof(entry));
        p->key = k;
        p->val[0] = i;
        p->val[1] = -1;
        HASH_ADD_INT(*hashMap, key, p);
        return true;
    } else {
        ret->val[1] = i;
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

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    returnSize[0] = 0;
    if (nums == NULL || numsSize <= 0) {
        return NULL;
    }
    
    int index1 = 0;
    int index2 = 0;
    int flag = 0;
    entry* hashMap = NULL;
    for (int i = 0; i < numsSize; i++) {
        AddHash(&hashMap, nums[i], i);
    }

    for (int i = 0; i < numsSize; i++) {
        index1 = i;
        entry* find = FindHash(&hashMap, target - nums[i]);
        if (find) {
            if (find->val[0] == i) {
                if (find->val[1] == -1) {
                    continue;
                } 
                index2 = find->val[1];
            } else {
                index2 = find->val[0];
            }
            flag = 1;
            break;
        }
    }
    FreeHash(&hashMap);

    if (flag) {
        returnSize[0] = 2;
        int* result = (int*)malloc(sizeof(int) * (returnSize[0] + 1));
        result[0] = index1;
        result[1] = index2;
        return result;
    }
    
    return NULL;
}

/*
int cmp(const void *a, const void *b){
    if (*(int*)a > *(int*)b) {
        return 1;
    }

    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    returnSize[0] = 0;
    if (nums == NULL || numsSize <= 0) {
        return NULL;
    }
    
    int qnums[numsSize + 1];
    memcpy(qnums, nums, sizeof(int) * numsSize);
    qsort(qnums, numsSize, sizeof(qnums[0]), cmp);

    int left = 0;
    int right = numsSize - 1;
    int flag = 0;
    while (left < right) {
        int tmp = qnums[left] + qnums[right];
        if (tmp == target) {
            flag = 1;
            break;
        } else if (tmp > target) {
            right--;
        } else {
            left++;
        }
    }

    if (flag) {
        int index1 = -1;
        int index2 = -1;
        for (int i = 0; i < numsSize; i++) {
            if (index1 == -1 && nums[i] == qnums[left]) {
                index1 = i;
            } else if (index2 == -1 && nums[i] == qnums[right]) {
                index2 = i;
            }

            if (index1 != -1 && index2 != - 1) {
                break;
            }
        }
        returnSize[0] = 2;
        int* result = (int*)malloc(sizeof(int) * (returnSize[0] + 1));
        result[0] = index1;
        result[1] = index2;
        return result;
    }

    return NULL;
}
*/
