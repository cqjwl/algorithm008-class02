#include <stdio.h>
#include <stdlib.h>
#include "solve.h"

void dfs(char** board, int m, int n, int i, int j) {

    if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] == 'X' || board[i][j] == '*') {
        return;
    }

    board[i][j] = '*';

    dfs(board, m, n, i - 1, j);
    dfs(board, m, n, i + 1, j);
    dfs(board, m, n, i, j - 1);
    dfs(board, m, n, i, j + 1);

}

void solve(char** board, int boardSize, int* boardColSize){

    if (board == NULL || boardSize <= 1 || boardColSize[0] <= 1) {
        return;
    }

    int m = boardSize;
    int n = boardColSize[0];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            int isEdge = 0;
            if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
                isEdge = 1;
            }
            if (isEdge && board[i][j] == 'O') {
                dfs(board, m, n, i, j);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O') {
                board[i][j] = 'X';
            } else if (board[i][j] == '*') {
                board[i][j] = 'O';
            }
        }
    }

    return;
}
