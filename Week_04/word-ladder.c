#include <stdio.h>
#include <stdlib.h>
#include "ladderLength.h"

#define MAX_STACK_SIZE 100000

bool isMatch(char *a, char *b) {
    int alen = strlen(a);
    int cnt = 0;
    for (int i = 0; i < alen; i++) {
        if (a[i] != b[i]) {
            cnt++;
            if (cnt > 1) {
                return false;
            }
        }
    }

    return cnt == 1;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
    if (beginWord == NULL || endWord == NULL || wordListSize <= 0) {
        return 0;
    }

    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(endWord, wordList[i]) == 0) {
            break;
        }
        if (i == wordListSize - 1) {
            return 0;
        }
    }

    int m = wordListSize;
    int visited[m + 1];
    memset(visited, 0, sizeof(int) * (m + 1));

    int cnt = 1;
    int inIndex = 0;
    int outIndex = 0;
    char* stack[MAX_STACK_SIZE] = {0};
    stack[inIndex++] = beginWord;
    while (outIndex < inIndex) {
        int len = inIndex - outIndex;
        for (int i = 0; i < len; i++) {
            char* temp = stack[outIndex++];
            if (strcmp(temp, endWord) == 0) {
                return cnt;
            }

            for (int j = 0; j < m; j++) {
                if (visited[j] == 0 && isMatch(temp, wordList[j])) {
                    visited[j] = 1;
                    stack[inIndex++] = wordList[j];
                }
            }
        }
        cnt++;
    }

    return 0;
}
