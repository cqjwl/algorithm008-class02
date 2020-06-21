#include <stdio.h>
#include <stdlib.h>
#include "firstUniqChar.h"

#define LETTER_SIZE 26

int firstUniqChar(char * s){
    int len = strlen(s);
    if (len == 0) {
        return -1;
    }

    int cnt[LETTER_SIZE] = {0};
    for (int i = 0; i < len; i++) {
        cnt[s[i] - 'a']++;
    }

    for (int i = 0; i < len; i++) {
        if (cnt[s[i] - 'a'] == 1) {
            return i;
        }
    }

    return -1;
}
