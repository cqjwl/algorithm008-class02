#include <stdio.h>
#include <stdlib.h>
#include "reverseWords.h"

void reverse(char* s, int left, int right){
    while (left < right) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        left++;
        right--;
    }

    return;
}

void removeSpace(char *s) {
    int i = 0;
    int j = 0;
    int len = strlen(s);
    for (i = 0; i < len; i++) {
        if (s[i] == ' ') {
            if (i && s[i] != s[i - 1]) {
                s[j] = s[i];
                j++;
            }
            continue;
        } else {
            s[j] = s[i];
            j++;
        }
    }

    if (j && s[j - 1] == ' ') {
        s[j - 1] = '\0';
        len = j - 1;
    } else {
        s[j] = '\0';
        len = j;
    }
}

char * reverseWords(char * s){
    removeSpace(s);
    int len = strlen(s);
    if (len == 0) {
        return s;
    }

    reverse(s, 0, len - 1);
    int left = 0;
    int right = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            right = i - 1;
            reverse(s, left, right);
            left = i + 1;
        }
    }

    reverse(s, left, len - 1);
    return s;
}
