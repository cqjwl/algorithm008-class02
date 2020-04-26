#include <stdio.h>
#include <stdlib.h>
#include "diameterOfBinaryTree.h"

int dfs(struct TreeNode* root, int* result){
    if (root == NULL) {
        return 0;
    }

    int left = dfs(root->left, result);
    int right = dfs(root->right, result);
    result[0] = fmax(result[0], left + right);

    return fmax(left, right) + 1;
}

int diameterOfBinaryTree(struct TreeNode* root){
    int result = 0;
    dfs(root, &result);
    return result;
}
