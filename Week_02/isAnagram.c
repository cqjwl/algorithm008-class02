#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h> 
#include "isAnagram.h"

bool isAnagram(char * s, char * t){
    if (s == NULL || t == NULL) {
        return false;
    }

    int slen = strlen(s);
    int tlen = strlen(t);
    if (slen != tlen) {
        return false;
    }

    int letter[26];
    memset(letter, 0, sizeof(int) * 26);

    for (int i = 0; i < slen; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            letter[s[i] - 'a'] += 1;
        }
        if (t[i] >= 'a' && t[i] <= 'z') {
            letter[t[i] - 'a'] -= 1;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (letter[i] != 0) {
            return false;
        }
    }

    return true;
}
