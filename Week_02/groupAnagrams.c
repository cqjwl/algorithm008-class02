#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "uthash.h"
#include "groupAnagrams.h"

typedef struct hash_entry {
    char key[30];
    int val[20];
    int cnt;
    UT_hash_handle hh;
} entry;

entry* FindHash(entry** hashMap, char *key){
    entry* ret = NULL;
    HASH_FIND_STR(*hashMap, key, ret);
    return ret;
}

bool AddHash(entry** hashMap, char *key, int i){
    entry* ret = NULL;
    HASH_FIND_STR(*hashMap, key, ret);
    if (ret == NULL) {
        entry* p = (entry*)malloc(sizeof(entry));
        strcpy(p->key, key);
        p->val[0] = i;
        p->cnt = 1;
        HASH_ADD_STR(*hashMap, key, p);
        return true;
    } else {
        ret->val[ret->cnt] = i;
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

int cmp (const void *a, const void *b) {
    if ((*(char*)a > *(char*)b)) {
        return 1;
    }
    return -1 ;
}

char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (strs == NULL || strsSize <= 0) {
        return NULL;
    }

    char **qstrs = (char**)malloc(sizeof(char*) * (strsSize + 1));
    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        qstrs[i] = (char*)malloc(sizeof(char) * (len + 1));
        strcpy(qstrs[i], strs[i]);
        qsort(qstrs[i], len, sizeof(qstrs[i][0]), cmp);
    }

    entry* hashMap = NULL;
    for (int i = 0; i < strsSize; i++) {
        AddHash(&hashMap, qstrs[i], i);
    }

    *returnSize = HASH_COUNT(hashMap);
    char ***result = (char***)malloc(sizeof(char**) * (*returnSize + 1));
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize + 1));
    entry* tmp;
    int j = 0;
    for (tmp = hashMap; tmp != NULL; tmp = tmp->hh.next) {
        result[j] = (char**)malloc(sizeof(char*) * (tmp->cnt));
        (*returnColumnSizes)[j] = tmp->cnt;
        for (int i = 0; i < tmp->cnt; i++) {
            result[j][i] = (char*)malloc(sizeof(char) * (strlen(tmp->key) + 1));
            strcpy(result[j][i], strs[tmp->val[i]]);
        }
        j++;
    }
    FreeHash(&hashMap);

    for (int i = 0; i < strsSize; i++) {
        free(qstrs[i]);
    }
    free(qstrs);

    return result;
}
