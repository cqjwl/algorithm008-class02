#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jump.h"

bool canJump(int* nums, int numsSize){
    if (nums == NULL | numsSize <= 0) {
        return true;
    }

    int end = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i <= end) {
            end = fmax(end, nums[i] + i);
        }
        if (end >= numsSize - 1) {
            return true;
        }
    }

    return false;
}
