#include <stdio.h>
#include <stdlib.h>
#include "splitArray.h"

int splitArray(int* nums, int numsSize, int m){
    int n = numsSize;

    long sub[n + 1];
    sub[0] = 0;
    for (int i = 0; i < n; i++) {
        sub[i + 1] = sub[i] + nums[i];
    }

    long dp[n + 1] [m + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) {
                dp[i][j] = fmin(dp[i][j], fmax(dp[k][j - 1], sub[i] - sub[k]));
            }
        }
    }

    return dp[n][m];
}
