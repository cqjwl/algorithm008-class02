#include <stdio.h>
#include <stdlib.h>
#include "search.h"

int search(int* nums, int numsSize, int target){
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }

    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[0] <= nums[mid]) {
            if (nums[0] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;  
            }
        } else {
            if (nums[mid] < target && target <= nums[numsSize - 1]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } 
    }

    return -1;
}
