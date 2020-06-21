#include <stdio.h>
#include <stdlib.h>
#include "isIsomorphic.h"

#define CHAR_SIZE 128

bool isIsomorphic(char * s, char * t){
    int sCnt[CHAR_SIZE] = {0};
    int tCnt[CHAR_SIZE] = {0};

    int sc = 0;
    int tc = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (sCnt[s[i]] == 0) {
            sCnt[s[i]] = ++sc;
        } 
        if (tCnt[t[i]] == 0) {
            tCnt[t[i]] = ++tc;
        } 
        if (sCnt[s[i]] != tCnt[t[i]]) {
            return false;
        }
    }

    return true;
}
