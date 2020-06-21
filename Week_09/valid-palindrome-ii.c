#include <stdio.h>
#include <stdlib.h>
#include "validPalindrome.h"

bool judge(char* s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        } else {
            left++;
            right--;
        }
    }

    return true;
}

bool validPalindrome(char * s){
    int len = strlen(s);

    int left = 0;
    int right = len - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return (judge(s, left + 1, right) || judge(s, left, right - 1));
        } else {
            left++;
            right--;
        }
    }

    return true;
}
