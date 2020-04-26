#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "preorder.h"

void getNodeSize(struct Node* root, int* n, int* level) {
    if (root == NULL) {
        return;
    }

    n[0]++;
    for (int i = 0; i < root->numChildren; i++) {
        level[0]++;
        getNodeSize(root->children[i], n, level);
    }

    return;
}

void getNodeVal(struct Node* root, int* result, int* index) {
    if (root == NULL) {
        return;
    }
    
    result[index[0]++] = root->val;
    for (int i = 0; i < root->numChildren; i++) {
        getNodeVal(root->children[i], result, index);
    }

    return;
}

int* preorder(struct Node* root, int* returnSize) {
    returnSize[0] = 0;
    if (root == NULL) {
        return NULL;
    }

    int n = 0;
    int level = 0;
    getNodeSize(root, &n, &level);

    int *result = (int*)malloc(sizeof(int) * (n + 1));
    int index = 0;
    getNodeVal(root, result, &index);

    returnSize[0] = n;
    return result;
}
