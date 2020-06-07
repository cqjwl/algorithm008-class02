#include <stdio.h>
#include <stdlib.h>
#include "minMutation.h"

int g_minstep = INT_MAX;

bool isMatch(char * curr, char * bank) {
    int cnt = 0;
    while(*bank != '\0') {
        if (*curr != *bank) {
            cnt++;
        }
        curr++;
        bank++;
    }

    if (cnt == 1) {
        return true;
    } else {
        return false;
    }
}

void dfs(char * start, char * end, char ** bank, int bankSize, int step, int* visited) {
    if (strcmp(start, end) == 0) {
        g_minstep = fmin(g_minstep, step);
        return;
    }

    for (int i = 0; i < bankSize; i++) {
        if (visited[i] == 0) {
            if (isMatch(start, bank[i])) {
                visited[i] = 1;
                dfs(bank[i], end, bank, bankSize, step + 1, visited);
                visited[i] = 0;
            }
        }
    }
}

int minMutation(char * start, char * end, char ** bank, int bankSize){
    if (bankSize <= 0) {
        return -1;
    }

    int visited[bankSize + 1];
    memset(visited, 0, sizeof(int) * (bankSize + 1));

    int step = 0;
    g_minstep = INT_MAX;
    dfs(start, end, bank, bankSize, step, visited);

    if (g_minstep == INT_MAX) {
        return -1;
    } else {
        return g_minstep;
    }
}
