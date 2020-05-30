#include <stdio.h>
#include <stdlib.h>
#include "maxCoins.h"

int maxCoins(int* nums, int numsSize){
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    int n = numsSize;
    int points[n + 2];
    points[0] = 1;
    points[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        points[i] = nums[i - 1];
    }

    int dp[n + 2][n + 2];
    memset(dp, 0, sizeof(int) * (n + 2) * (n + 2));

    for (int i = n; i >=0; i--) {
        for (int j = i + 1; j < n + 2; j++) {
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = fmax(dp[i][j], 
                                dp[i][k] + dp[k][j] + points[i] * points[j] * points[k]);
            }
        }
    }

    return dp[0][n + 1];
}
