#include <stdio.h>
#include <stdlib.h>
#include "climbStairs.h"

int helper(int n, int dp1, int dp2){
    if (n <= 1) {
        return dp1;
    }

    if (n == 2) {
        return dp2;
    }

    return helper(n - 1, dp2, dp2 + dp1);
}

int climbStairs(int n){
    return helper(n, 1, 2);
}
