#include <stdio.h>
#include <stdlib.h>
#include "findCircleNum.h"

int find(int* fa, int i){
    if (fa[i] == i) {
        return i;
    }

    return fa[i] = find(fa, fa[i]);
}

int findCircleNum(int** M, int MSize, int* MColSize){
    int n = MSize;
    int m = MColSize[0];
    if (n == 0 || m == 0) {
        return 0;
    }

    int fa[n];
    for (int i = 0; i < n; i++) {
       fa[i] = i;
    }

    int ans = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (M[i][j] == 0) {
                continue;
            }

            if (find(fa, fa[i]) != find(fa, fa[j])) {
                fa[find(fa, i)] = fa[find(fa, j)];
                ans--;
            }
        }
    }

    return ans;
}
