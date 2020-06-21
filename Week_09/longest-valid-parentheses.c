#include <stdio.h>
#include <stdlib.h>
#include "numDistinct.h"

int numDistinct(char * s, char * t){
    int slen = strlen(s);
    int tlen = strlen(t);
    long dp[slen + 1];
    for (int i = 0; i <= slen; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i <= tlen; i++) {
        long pre = dp[0];
        dp[0] = 0;
        for (int j = 1; j <= slen; j++) {
            int tmp = dp[j];
            if (t[i - 1] == s[j - 1]) {
                dp[j] = dp[j - 1] + pre;
            } else {
                dp[j] = dp[j - 1];
            }
            pre = tmp;
        }
    }

    return (int)dp[slen];
}
