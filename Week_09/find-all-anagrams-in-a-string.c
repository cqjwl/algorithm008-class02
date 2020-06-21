#include <stdio.h>
#include <stdlib.h>
#include "findAnagrams.h"

#define LETTER_SIZE 26
#define MAX_STRING_LEN 20100

int* findAnagrams(char * s, char * p, int* returnSize){
    if (s == NULL || p == NULL || returnSize == NULL) {
        return NULL;
    }

    int cnt[LETTER_SIZE] = {0};
    int plen = strlen(p);
    int i = 0;
    for (; i < plen; i++) {
        cnt[p[i] - 'a']++;
    }
    
    int *ans = (int *)malloc(sizeof(int) * MAX_STRING_LEN);
    memset(ans, 0, sizeof(int) * MAX_STRING_LEN);

    int slen = strlen(s);
    int begin = 0; 
    int end = 0; 
    int j = 0;
    for (; end < slen; end++) {
        cnt[s[end] - 'a']--;

        while (cnt[s[end] - 'a'] < 0) {
            cnt[s[begin] - 'a']++;
            begin++;
        }

        if (plen == end - begin + 1) {
            ans[j] = begin;
            j++;

            cnt[s[begin] - 'a']++;
            begin = begin + 1;
        }
    }
    
    *returnSize = j;
    return ans;
}
