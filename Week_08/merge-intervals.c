#include <stdio.h>
#include <stdlib.h>
#include "merge.h"

int cmp(const void *a , const void *b) 
{   
    int* ptrA = *(int **)a;
    int* ptrB = *(int **)b;

    return (ptrA[0] > ptrB[0]) ? 1 : -1; 
} 

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    if (intervalsSize == 0) {
        returnSize[0]= 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int n = intervalsSize;
    int m = intervalsColSize[0];

    qsort(intervals, n, sizeof(intervals[0]), cmp);

    int stack[n * m];
    int top = -1;
    stack[++top] = intervals[0][0];
    stack[++top] = intervals[0][1];
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] <= stack[top]) {
            if (stack[top] < intervals[i][1]) {
                stack[top] = intervals[i][1];
            }
        } else {
            stack[++top] = intervals[i][0];
            stack[++top] = intervals[i][1];
        }
    }

    n = (top + 1) / 2;
    int** ans = (int**)malloc(sizeof(int*) * n);
    int* ansColSize = (int*)malloc(sizeof(int) * n);
    returnSize[0] = n;

    int j = -1;
    for (int i = 0; i < n; i++) {
        ans[i] = (int*)malloc(sizeof(int) * m);
        ansColSize[i] = m;
        ans[i][0] = stack[++j];
        ans[i][1] = stack[++j];
    }

    *returnColumnSizes = ansColSize;
    return ans;
}
