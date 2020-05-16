#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "searchMatrix.h"

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target){
    if (matrixSize <= 0 || matrixColSize[0] <= 0) {
        return false;
    }

    int row = 0;
    int col = matrixColSize[0] - 1;
    while (row < matrixSize) {
        if (target > matrix[row][col]) {
            row++;
        } else if (target == matrix[row][col]) {
            return true;
        } else {
            int left = 0;
            int right = col;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (target == matrix[row][mid]) {
                    return true;
                }
                if (target > matrix[row][mid]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return false;
        }
    }

    return false;
}
