#include <stdio.h>
#include <stdlib.h>
#include "maxDepth.h"

int maxDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }

    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    return fmax(leftDepth, rightDepth) + 1;
}
