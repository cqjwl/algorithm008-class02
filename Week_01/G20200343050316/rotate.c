#include <stdio.h>
#include <stdlib.h>
#include "rotate.h"

/*
void rotate(int* nums, int numsSize, int k){
    if (nums == NULL || numsSize <= 1 || k <= 0) {
        return;
    }

    k = k % numsSize;
    printf("k = %d\n", k);
    for (int i = 0; i < k; i++) {
        int tmp = nums[numsSize - 1];
        for (int j = numsSize - 1; j > 0; j--) {
            nums[j] = nums[j - 1];
            printf("nums[%d] = %d\n", j, nums[j]);
        }
        nums[0] = tmp;
    }

    return;
}
*/

void rotate(int* nums, int numsSize, int k){
    if (nums == NULL || numsSize <= 1 || k <= 0) {
        return;
    }

    k = k % numsSize;
    if (k == 0) {
        return;
    }

    int temp[k];
    for (int i = 0; i < k; i++) {
        temp[i] = nums[numsSize - k + i];
    } 

    for (int i = 0; i < numsSize - k; i++) {
        nums[numsSize - 1 - i] = nums[numsSize - 1 - k -i];
    }

    for (int i = 0; i < k; i++) {
        nums[i] = temp[i];
    }

    return;
}

