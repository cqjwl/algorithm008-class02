#include <stdio.h>
#include <stdlib.h>
#include "longestValidParentheses.h"

//dp
int longestValidParentheses(char * s){
    int len = strlen(s);
    if (len <= 1) {
        return 0;
    }

    int dp[len];
    memset(dp, 0, sizeof(int) * len);

    int ans = 0;
    for(int i = 1; i < len; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = 2;
                if (i - 2 >= 0) {
                    dp[i] = dp[i] + dp[i - 2];
                }
            } else if (dp[i - 1] > 0) {
                if ((i - dp[i - 1] - 1) >= 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + 2;
                    if ((i - dp[i - 1] - 2) >= 0) {
                        dp[i] = dp[i] + dp[i - dp[i - 1] - 2];
                    }
                }
            }
        }
        ans = fmax(ans, dp[i]);
    }

    return ans;
}

//正、反向2次遍历
int longestValidParentheses(char * s){
    int len = strlen(s);
    if (len <= 1) {
        return 0;
    }

    int left = 0;
    int right = 0;
    int ans = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            ans = fmax(ans, left * 2);
        } else if (right > left) {
            left = 0;
            right = 0;
        }
    }

    left = 0;
    right = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            ans = fmax(ans, right * 2);
        } else if (left > right) {
            left = 0;
            right = 0;
        }
    }

    return ans;
}
