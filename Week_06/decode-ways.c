#include <stdio.h>
#include <stdlib.h>
#include "numDecodings.h"

int numDecodings(char * s){
    if (s == NULL || s[0] == '0') {
        return 0;
    }

    int len = strlen(s);

    int dp[len];
    dp[0] = 1;
    int val = 0;
    if (len > 1) {
        if (s[1] == '0') {
            val = 10 * (s[0] - '0')+ s[1] - '0';
            if ( val <= 26) {
                dp[1] = 1;
            } else {
                return 0;
            }            
        }else {
            val = 10 * (s[0] - '0')+ s[1] - '0';
            if (val <= 26) {
                dp[1] = 2;
            } else {
                dp[1] = 1;
            }
        }
    } else {
        return 1;
    }

    for (int i = 2; i < len; i++) {
        if (s[i] == '0') {
            if (s[i - 1] == '0') {
                return 0;
            } else {
                val = 10 * (s[i - 1] - '0')+ s[i] - '0';
                if ( val <= 26) {
                    dp[i] = dp[i - 2];
                } else {
                    return 0;
                }                            
            }
        } else {
            if (s[i - 1] == '0') {
                dp[i] = dp[i - 1];
            } else {
                val = 10 * (s[i - 1] - '0')+ s[i] - '0';
                if ( val <= 26) {
                    dp[i] = dp[i - 1] + dp[i - 2];
                } else {
                    dp[i] = dp[i - 1];
                }                            
            }            
        }
    }

    return dp[len - 1];
}
