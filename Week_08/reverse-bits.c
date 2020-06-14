#include <stdio.h>
#include <stdlib.h>
#include "reverseBits.h"

uint32_t reverseBits(uint32_t n) {
    long ans = 0;
    for (int i = 0; i < 32; i++) {
        ans = (ans << 1) + (n & 1);
        n = n >> 1;
    }

    return (int)ans;
}
