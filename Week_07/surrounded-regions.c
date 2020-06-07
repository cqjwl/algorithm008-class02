#include <stdio.h>
#include <stdlib.h>
#include "numIslands.h"

void dfs(char** grid, int m, int n, int i, int j, int** visited) {
    if (grid[i][j] == '0') {
        visited[i][j] = 1;
        return;
    }

    grid[i][j] = '0';
    visited[i][j] = 1;
    if (i - 1 >= 0 && visited[i - 1][j] == 0) {
        dfs(grid, m, n, i - 1, j, visited);
    }

    if (i + 1 < m && visited[i + 1][j] == 0) {
        dfs(grid, m, n, i + 1, j, visited);
    }

    if (j - 1 >= 0 && visited[i][j - 1] == 0) {
        dfs(grid, m, n, i, j - 1, visited);
    }

    if (j + 1 < n && visited[i][j + 1] == 0) {
        dfs(grid, m, n, i, j + 1, visited);
    }

    return;
}

int numIslands(char** grid, int gridSize, int* gridColSize){
    if (gridSize <= 0 || gridColSize[0] <= 0) {
        return 0;
    }

    int m = gridSize;
    int n = gridColSize[0];

    int visited[m + 1][n + 1];
    memset(visited, 0, sizeof(int) * (m + 1) * (n + 1));

    int *pvisited[m + 1];
    for (int i = 0; i < m; i++){
        pvisited[i] = &visited[i];
    }
 
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j] == 1) {
                continue;
            } else {
                if (grid[i][j] == '1') {
                    cnt++;
                    dfs(grid, m, n, i, j, pvisited);
                }
            }
        }
    }

    return cnt;
}
