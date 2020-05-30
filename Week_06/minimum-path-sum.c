#include <stdio.h>
#include <stdlib.h>
#include "minPathSum.h"

int minPathSum(int** grid, int gridSize, int* gridColSize){
    if (gridSize <= 0 || gridColSize[0] <= 0) {
        return 0;
    }

    int n = gridSize;
    int m = gridColSize[0];

    int dp[n][m];
    dp[0][0] = grid[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            if (i == 0) {
                dp[i][j] = dp[i][j - 1] + grid[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + grid[i][j];
            } else {
                dp[i][j] = fmin(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
    }

    return dp[n - 1][m - 1];
}
