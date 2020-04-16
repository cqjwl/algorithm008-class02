#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "twoSum.h"

int cmp(const void *a, const void *b){
    if (*(int*)a > *(int*)b) {
        return 1;
    }

    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    if (nums == NULL || numsSize <= 0) {
        returnSize[0] = 0;
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

    returnSize[0] = 0;
    return NULL;
}

