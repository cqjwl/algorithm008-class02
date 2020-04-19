#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "balancedStringSplit.h"

int balancedStringSplit(char * s){
    if (s == NULL) {
        return 0;
    }

    int len = strlen(s);
    if (len <= 1) {
        return 0;
    }

    int cntL = 0;
    int cntR = 0;
    int result = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == 'L') {
            cntL++;
        } else {
            cntR++;
        }

        if (cntL == cntR) {
            result += 1;
            cntL = 0;
            cntR = 0;
        }
    }

    return result;
}
