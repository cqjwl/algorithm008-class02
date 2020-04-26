#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "nthUglyNumber.h"

int nthUglyNumber(int n){
    int dp[n];
    int i2 = 0;
    int i3 = 0;
    int i5 = 0;
    int i = 0;

    memset(dp, 0, sizeof(int) * n);
    dp[0] = 1;

    for (i = 1; i < n; i++) {
        dp[i] = fmin(dp[i2] * 2, fmin(dp[i3] * 3, dp[i5] * 5));

        if (dp[i] == dp[i2] * 2) {
            i2++;
        }

        if (dp[i] == dp[i3] * 3) {
            i3++;
        }

        if (dp[i] == dp[i5] * 5) {
            i5++;
        }
    }

    return dp[i - 1];
}
