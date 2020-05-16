#include <stdio.h>
#include <stdlib.h>
#include "findContentChildren.h"

int cmp(const void *a, const void *b){
    if (*(int*)a > *(int*)b) {
        return 1;
    }
    return -1;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){
    if (g == NULL || gSize <= 0 || s == NULL | sSize <= 0) {
        return 0;
    }

    qsort(g, gSize, sizeof(g[0]), cmp);
    qsort(s, sSize, sizeof(s[0]), cmp);

    int cnt = 0;
    int i = 0;
    int j = 0;
    while (i < gSize && j < sSize) {
        if (s[j] >= g[i]) {
            cnt++;
            i++;
        }
        j++;
    }

    return cnt;
}
