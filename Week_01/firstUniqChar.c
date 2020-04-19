#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "firstUniqChar.h"

char firstUniqChar(char* s){
    char result = ' ';
    if (s == NULL) {
        return result;
    }

    int len = strlen(s);
    if (len == 0) {
        return result;
    }

    int letter[26];
    memset(letter, 0, sizeof(int) * 26);
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            letter[s[i] - 'a']++;
        }
    }

    for (int i = 0; i < len; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            if (letter[s[i] - 'a'] == 1) {
                result = s[i];
                break;
            }
        }
    }

    return result;
}
