#include <stdio.h>
#include <stdlib.h>
#include "findMin.h"

int findMin(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }

    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return nums[left];
}
