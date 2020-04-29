#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "permute.h"

void backtrack(int* used, int start, int* stack, int* nums, int numsSize, int** result, int* resultSize, int *resultColSize){
    if (start == numsSize) {
        int *temp = (int*)malloc(sizeof(int) * numsSize);
        memset(temp, 0, sizeof(int) * numsSize);
        for (int i = 0; i < numsSize; i++){
            temp[i] = stack[i];
        }

        result[resultSize[0]] = temp;
        resultColSize[resultSize[0]] = numsSize;
        resultSize[0]++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i] == 0) {
            stack[start] = nums[i];
            used[i] = 1;
            backtrack(used, start + 1, stack, nums, numsSize, result, resultSize, resultColSize);
            used[i] = 0;
        }
    }

    return;
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    if (nums == NULL || numsSize <= 0) {
        returnSize[0] = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int used[numsSize];
    memset(used, 0, sizeof(int) * numsSize);
    int start = 0;
    int stack[10000];
    memset(stack, 0, sizeof(int) * 10000);

    int **result = (int**)malloc(sizeof(int) * 10000);
    int resultSize = 0;
    int *resultColSize = (int*)malloc(sizeof(int) * 10000);

    backtrack(used, start, stack, nums, numsSize, result, &resultSize, resultColSize);

    *returnColumnSizes = resultColSize;
    returnSize[0] = resultSize;
    return result;
}
