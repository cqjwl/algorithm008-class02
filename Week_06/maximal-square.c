#include <stdio.h>
#include <stdlib.h>
#include "maximalSquare.h"

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize){
    if(matrixSize <= 0) {
        return 0;
    }

    int n = matrixSize;
    int m = matrixColSize[0];

    int width[n][m];
    memset(width, 0, sizeof(int) * (n * m));

    int maxArea = 0;
    int maxHeight = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (matrix[row][col] == '1') {
                if (col == 0) {
                    width[row][col] = 1;
                } else {
                    width[row][col] = width[row][col - 1] + 1;
                }
            } else {
                width[row][col] = 0;
            }

            int minWidth = width[row][col];
            if(minWidth <= maxHeight ) {
                continue;
            }

            for (int up_row = row; up_row >= 0; up_row--) {
                int height = row - up_row + 1;
                minWidth = fmin(minWidth, width[up_row][col]);
                if (height > minWidth ) {
                    break;
                }

                if (height == minWidth) {
                    maxArea = fmax(maxArea, height * minWidth);
                    maxHeight = fmax(maxHeight, height);
                }
            }
        }
    }

    return maxArea;
}
