#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "reverseOnlyLetters.h"

char * reverseOnlyLetters(char * S){
    if (S == NULL) {
        return NULL;
    }

    int len = strlen(S);
    if (len == 0) {
        return S;
    }

    int i = 0;
    int j = len - 1;
    while (i < j) {
        int iLetter = 0;
        int jLetter = 0;
        if (S[i] >= 'a' && S[i] <= 'z' || S[i] >= 'A' && S[i] <= 'Z') {
            iLetter = 1;
        } 
        if (S[j] >= 'a' && S[j] <= 'z' || S[j] >= 'A' && S[j] <= 'Z') {
            jLetter = 1;
        } 
        
        if (iLetter && jLetter) {
            char tmp = S[i];
            S[i] = S[j];
            S[j] = tmp;
            i++;
            j--;
        } else if (iLetter == 0) {
            i++;
        } else if (jLetter == 0) {
            j--;
        }
        
    }

    return S;
}
