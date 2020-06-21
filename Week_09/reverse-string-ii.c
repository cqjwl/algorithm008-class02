#include <stdio.h>
#include <stdlib.h>
#include "reverseStr.h"

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

char * reverseStr(char * s, int k){
    int len = strlen(s);
    if (len == 0 || len == 1 || k == 1) {
        return s;
    }

    int i = 0;
    int begin = 0;
    int end = 0;
    int left = 0;
    int right = 0;
    while (begin < len) {
        end = begin + 2 * k - 1;
        if (end < len) {
            left = begin;
            right = begin + k - 1;
        } else {
            if (len - begin < k) {
                left = begin; 
                right = len - 1;
            } else {
                left = begin;
                right = begin + k - 1;
            }
        }
        reverse(s, left, right);
        i++;
        begin = 2 * k * i;
    }

    return s;
}
