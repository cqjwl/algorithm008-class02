#include <stdio.h>
#include <stdlib.h>
#include "setZeroes.h"

void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    if (matrix == NULL || (matrixSize <= 1 && matrixColSize <= 1)) {
        return;
    }

    int m = matrixSize;
    int n = *matrixColSize;

    int matched[m][n];
    for (int i = 0; i < m; i++) {
        memset(matched[i], 0, sizeof(int) * (n));
    }

    int k = 0;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            if (matrix[i][j] == 0) {
                k = i - 1;
                while (k >= 0) {
                    if (matrix[k][j] != 0) {
                        matched[k][j] = 1;
                    }
                    k--;
                }
                k = i + 1;
                while (k < matrixSize) {
                    if (matrix[k][j] != 0) {
                        matched[k][j] = 1;
                    }
                    k++;
                }
                k = j - 1;
                while (k >= 0) {
                    if (matrix[i][k] != 0) {
                        matched[i][k] = 1;
                    }
                    k--;
                }
                k = j + 1;
                while (k < matrixColSize[i]) {
                    if (matrix[i][k] != 0) {
                        matched[i][k] = 1;
                    }
                    k++;
                }
            }
        }
    }

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            if (matched[i][j] == 1) {
                matrix[i][j] = 0;
            }
        }
    }

    return;
}
