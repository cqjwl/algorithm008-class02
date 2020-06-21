#include <stdio.h>
#include <stdlib.h>
#include "racecar.h"

int racecar(int target){
    int dp[target + 1];
    for (int i = 1; i <= target; ++i) {
        dp[i] = INT_MAX;
        int j = 1, cnt1 = 1;
        for (; j < i; j = (1 << ++cnt1) - 1) {
            for (int k = 0, cnt2 = 0; k < j; k = (1 << ++cnt2) - 1) {
                dp[i] = fmin(dp[i], cnt1 + 1 + cnt2 + 1 + dp[i - (j - k)]);
            }
        }
        dp[i] = fmin(dp[i], cnt1 + (i == j ? 0 : 1 + dp[j - i]));
    }
    
    return dp[target];
}
