#include <stdio.h>
#include <stdlib.h>
#include "sortedSquares.h"

int* sortedSquares(int* A, int ASize, int* returnSize){
    if (A == NULL || ASize <= 0) {
        returnSize[0] = 0;
        return NULL;
    }

    int *result = (int*)malloc(sizeof(int) * (ASize + 1));

    int i = 0;
    int j = 0;
    int k = 0;
    while (j < ASize && A[j] < 0) {
        j++;
    }
    i = j - 1;

    while (i >= 0 && j < ASize) {
        int tmpi = A[i] * A[i];
        int tmpj = A[j] * A[j];
        if (tmpi > tmpj) {
            result[k++] = tmpj;
            j++;
        } else {
            result[k++] = tmpi;
            i--;
        }
    }

    while (i >= 0) {
        result[k++] = A[i] * A[i];
        i--;
    }

    while (j < ASize) {
        result[k++] = A[j] * A[j];
        j++;
    }

    returnSize[0] = ASize;
    return result;
}
