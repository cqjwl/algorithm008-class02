#include <stdio.h>
#include <stdlib.h>
#include "isPowerOfTwo.h"

bool isPowerOfTwo(int n){
    if (n < 0) {
        return false;
    }
    
    int cnt = 0;
    while (n) {
        cnt++;
        n &= n - 1;
    }

    return cnt == 1;
}
