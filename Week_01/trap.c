#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "trap.h"

int trap(int* height, int heightSize){
    if(height == NULL || heightSize <= 0){
        return 0;
    }

    int left = 0, right = heightSize - 1;
    int left_max = 0, right_max = 0;
    int result = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            if (left_max > height[left]) {
                result += left_max - height[left]; 
                left++;
            } else {
                left_max = height[left];
                left++;
            }
        } else {
            if (right_max > height[right]) {
                result += right_max - height[right]; 
                right--;
            } else {
                right_max = height[right];
                right--;
            }
        }
    }

    return result;
}
