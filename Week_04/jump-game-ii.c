#include <stdio.h>
#include <stdlib.h>
#include "jump.h"

int jump(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 1) {
        return 0;
    }

    int end = 0;
    int maxPos = 0;
    int result = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        maxPos = fmax(maxPos, nums[i] + i);
        if (i == end) {
            end = maxPos;
            result++;
        }
    }

    return result;
}
