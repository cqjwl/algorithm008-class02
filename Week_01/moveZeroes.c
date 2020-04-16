#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "moveZeroes.h"
/*
void moveZeroes(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 1) {
        return;
    }
    
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[j] = nums[i];
            j++;
        }
    }

    for (; j < numsSize; j++) {
        nums[j] = 0;
    }
    
    return;
}
*/

void moveZeroes(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 1) {
        return;
    }
    
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            int tmp = nums[j];
            nums[j] = nums[i];
            nums[i] = tmp;
            j++;
        }
    }

    return;
}
