#include <stdio.h>
#include <stdlib.h>
#include "relativeSortArray.h"

#define LEN_SIZE 1001

int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize){
    int cnt[LEN_SIZE] = {0};
    int i = 0;
    for (i = 0; i < arr1Size; i++) {
        cnt[arr1[i]]++;
    }

    int j = 0;
    for (i = 0; i < arr2Size; i++) {
        while(cnt[arr2[i]]) {
            arr1[j++] = arr2[i];
            cnt[arr2[i]]--;
        }
    }

    for (i = 0; i < LEN_SIZE; i++) {
        while(cnt[i]) {
            arr1[j++] = i;
            cnt[i]--;
        }
    }

    *returnSize = arr1Size;
    return arr1;
}
