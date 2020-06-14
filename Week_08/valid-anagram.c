#include <stdio.h>
#include <stdlib.h>
#include "isAnagram.h"

#define LETTER_SIZE 26

bool isAnagram(char * s, char * t){
    if (s == NULL || t == NULL) {
        return false;
    }

    int slen = strlen(s);
    int tlen = strlen(t);
    if (slen != tlen) {
        return false;
    }

    int letter[LETTER_SIZE] = {0};
    for (int i = 0; i < slen; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            letter[s[i] - 'a'] += 1;
        }
        if (t[i] >= 'a' && t[i] <= 'z') {
            letter[t[i] - 'a'] -= 1;
        }
    }

    for (int i = 0; i < LETTER_SIZE; i++) {
        if (letter[i] != 0) {
            return false;
        }
    }

    return true;
}
