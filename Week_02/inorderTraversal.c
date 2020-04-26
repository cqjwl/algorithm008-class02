#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "inorderTraversal.h"

void treeInorder(struct TreeNode* root, int* returnSize, int *result){
    if (root == NULL){
        return;
    }

    treeInorder(root->left, returnSize, result);
    result[returnSize[0]++] = root->val;
    treeInorder(root->right, returnSize, result);
}

int treeSize(struct TreeNode* root){
    if (root == NULL){
        return 0;
    }

    return treeSize(root->left) + treeSize(root->right) + 1;
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int *result = NULL;

    if (root == NULL){
        returnSize[0] = 0;
        return result;
    }

    int nums = treeSize(root);

    result = (int*)malloc(sizeof(int) * nums);
    memset(result, 0, sizeof(int) * nums);

    returnSize[0] = 0;
    treeInorder(root, returnSize, result);

    return result;   
}
