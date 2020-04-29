#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "combine.h"

void backtrack(int n, int k, int start, int* stack, int *top, int** result, int* resultSize, int *resultColSize){
    if (top[0] == k - 1) {
        int *temp = (int*)malloc(sizeof(int) * k);
        memset(temp, 0, sizeof(int) * k);
        for (int i = 0; i <= top[0]; i++){
            temp[i] = stack[i];
        }

        result[resultSize[0]] = temp;
        resultColSize[resultSize[0]] = k;
        resultSize[0]++;
        return;
    }

    for (int i = start; i <= n; i++) {
        stack[++top[0]] = i;
        backtrack(n, k, i + 1, stack, top, result, resultSize, resultColSize);
        top[0]--;
    }

    return;
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
    if (n == 0 || k <= 0) {
        returnSize[0] = 0;
        *returnColumnSizes = NULL;
        return NULL;
    } 

    int stack[10000];
    int top = -1;
    memset(stack, 0, sizeof(int) * 10000);

    int **result = (int**)malloc(sizeof(int) * 10000);
    int resultSize = 0;
    int *resultColSize = (int*)malloc(sizeof(int) * 10000);

    int start = 1;
    backtrack(n, k, start, stack, &top, result, &resultSize, resultColSize);

    *returnColumnSizes = resultColSize;
    returnSize[0] = resultSize;
    return result;
}
