#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "robotSim.h"

typedef struct hash_entry {
    char key[30];
    UT_hash_handle hh;
} entry;

entry* FindHash(entry** hashMap, char *key){
    entry* ret = NULL;
    HASH_FIND_STR(*hashMap, key, ret);
    return ret;
}

bool AddHash(entry** hashMap, char *key){
    entry* ret = NULL;
    HASH_FIND_STR(*hashMap, key, ret);
    if (ret == NULL) {
        entry* p = (entry*)malloc(sizeof(entry));
        int len = strlen(key);
        strncpy(p->key, key,len + 1);
        HASH_ADD_STR(*hashMap, key, p);
        return true;
    } else {
        return false;
    }     
}

void FreeHash(entry** hashMap){  
    entry *current_entry, *tmp;  
    HASH_ITER(hh, *hashMap, current_entry, tmp) {  
    HASH_DEL(*hashMap,current_entry);    
    free(current_entry);              
    }  
}

int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize){
    if (commands == NULL || commandsSize <= 0) {
        return 0;
    }

    entry* hashMap = NULL;
    for (int i = 0; i < obstaclesSize; i++) {
        char key[30];
        key[29] = '\0';
        sprintf(key, "%d:%d", obstacles[i][0], obstacles[i][1]);
        AddHash(&hashMap, key);
    }

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int di = 0;
    
    int x = 0;
    int y = 0; 
    int i = 0;
    int result = 0;
    while (i < commandsSize) {
        if (commands[i] == -2) {
            di = (di + 3) % 4;
        } else if (commands[i] == -1) {
            di = (di + 1) % 4;
        } else if (1 <= commands[i] && commands[i] <= 9) {
            for (int k = 0; k < commands[i]; k++) {
                int nx = x + dx[di];
                int ny = y + dy[di];
                char key[30];
                key[29] = '\0';
                sprintf(key, "%d:%d", nx, ny);
                entry* find = FindHash(&hashMap, key);
                if (find) {
                    break;
                } else {
                    x = nx;
                    y = ny;
                    result = fmax(result, x * x + y * y);
                } 
            }
        } 
        i++;
    }

    FreeHash(&hashMap);
    return result; 
}
