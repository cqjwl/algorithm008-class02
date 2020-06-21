#include <stdio.h>
#include <stdlib.h>
#include "lengthOfLIS.h"

//dp
int lengthOfLIS(int* nums, int numsSize){
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    int dp[numsSize];
    dp[0] = 1;
    int ans = 1;
    for (int i = 1; i < numsSize; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
        ans = fmax(ans, dp[i]);
    }

    return ans;
}

//二分查找
int lengthOfLIS(int* nums, int numsSize){
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    int top[numsSize];
    memset(top, 0, sizeof(int) * numsSize);
    
    int ans = 0;
    for (int i = 0; i < numsSize; i++) {
        int tmp = nums[i];
        int left = 0;
        int right = ans;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (top[mid] >= tmp) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        if (left == ans) {
            ans++;
        }

        top[left] = tmp;
    }

    return ans;
}
