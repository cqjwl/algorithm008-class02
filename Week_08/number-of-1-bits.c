#include <stdio.h>
#include <stdlib.h>
#include "hammingWeight.h"

int hammingWeight(uint32_t n) {
    int cnt = 0;
    while (n) {
        cnt++;
        n &= n - 1;
    }

    return cnt;
}
