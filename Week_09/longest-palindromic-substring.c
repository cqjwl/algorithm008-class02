#include <stdio.h>
#include <stdlib.h>
#include "longestPalindrome.h"

int expandAroundCenter(char * s, int L, int R) {
    int len = strlen(s);
    while (L >= 0 && R < len && s[L] == s[R]) {
        L--;
        R++;
    }
    return R - L - 1;
}

char * longestPalindrome(char * s){
    int slen = strlen(s);
    if (slen == 0) {
        return "";
    }

    int begin = 0;
    int end = 0;
    for (int i = 0; i < slen; i++) {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int len = fmax(len1, len2);
        if (len > end - begin) {
            begin = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }

    char* ans = (char*)malloc(sizeof(char) * (end - begin + 2));
    int j = 0;
    for (int i = begin; i <= end; i++) {
        ans[j++] = s[i];
    }
    ans[j] = '\0';

    return ans;
}
