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

char * reverseWords(char * s){
    int len = strlen(s);

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
