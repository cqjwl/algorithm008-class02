#include <stdio.h>
#include <stdlib.h>
#include "minDistance.h"

int min(int a, int b, int c) {
    return fmin(a, fmin(b, c));
}

int minDistance(char * word1, char * word2){
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    int dp[len1 + 1][len2 + 1];

    int i = 0;
    int j = 0;

    for (i = 0; i <= len1; i++) {
        dp[i][0] = i;
    }

    for (j = 0; j <= len2; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1);
            }
        }
    }

    return dp[len1][len2];
}
