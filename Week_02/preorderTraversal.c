#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "preorderTraversal.h"

int treeSize(struct TreeNode* root){
    if (root == NULL){
        return 0;
    }

    return treeSize(root->left) + treeSize(root->right) + 1;
}

void helper(struct TreeNode* root, int *result, int* returnSize) {
    if (root == NULL) {
        return;
    }
    result[returnSize[0]++] = root->val;

    helper(root->left, result, returnSize);
    helper(root->right, result, returnSize);

    return;
}

int* preorderTraversal(struct TreeNode* root, int* returnSize){

    int *result = NULL;

    returnSize[0] = 0;
    if (root == NULL || returnSize == NULL) {
        return result;
    }

    int nums = treeSize(root);
    if (nums == 0) {
        return result;
    }

    result = (int*)malloc(sizeof(int) * (nums + 1));
    helper(root, result, returnSize);

    return result;
}
