#include <stdio.h>
#include <stdlib.h>
#include "plusOne.h"

int* plusOne(int* digits, int digitsSize, int* returnSize){
    if (digits == NULL || digitsSize <= 0) {
        returnSize[0] = 0;
        return NULL;
    }

    int carry = 1;
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (carry == 1) {
            int tmp = digits[i] + carry;
            if (tmp == 10) {
                digits[i] = 0;
                carry = 1;
            } else {
                digits[i] = tmp;
                carry = 0;
                break;
            }
        } else {
            break;
        }
    }

    int* result = digits;
    returnSize[0] = digitsSize;
    if (carry) {
        returnSize[0] = digitsSize + 1;
        result = (int*)malloc(sizeof(int) * (returnSize[0] + 1));

        result[0] = carry;
        for (int i = 0; i < digitsSize; i++) {
            result[i + 1] = digits[i];
        }
    }

    return result;
}

