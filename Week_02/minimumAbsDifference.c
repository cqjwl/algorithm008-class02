#include <stdio.h>
#include <stdlib.h>
#include "minimumAbsDifference.h"

int cmp(const void *a, const void *b) {
    if (*(int*)a > *(int*)b) {
        return 1;
    }
    return -1;
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (arr == NULL || arrSize <= 1) {
        return NULL;
    }

    qsort(arr, arrSize, sizeof(arr[0]), cmp);

    int diff[arrSize];
    diff[0] = 0;
    int min = INT_MAX;
    int cnt = 0;
    for (int i = 1; i < arrSize; i++) {
        diff[i] = arr[i] - arr[i - 1];
        if (diff[i] < min) {
            min = diff[i];
            cnt = 1;
        } else if (diff[i] == min) {
            cnt += 1;
        }
    }

    *returnSize = cnt;
    *returnColumnSizes = (int*)malloc(sizeof(int) * (cnt + 1));
    int **result = (int**)malloc(sizeof(int*) * (cnt + 1));
    for (int i = 0; i < cnt; i++) {
        (*returnColumnSizes)[i] = 2;
        result[i] = (int*)malloc(sizeof(int) * ((*returnColumnSizes)[i] + 1));
    }

    int j = 0;
    for (int i = 1; i < arrSize; i++) {
        if (diff[i] == min) {
            result[j][0] = arr[i - 1];
            result[j][1] = arr[i];
            j++;
        }
    }

    return result;
}
