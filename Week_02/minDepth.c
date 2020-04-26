#include <stdio.h>
#include <stdlib.h>
#include "minDepth.h"

int minDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }

    if ((root->left == NULL) && (root->right == NULL)) {
      return 1;
    }

    int min_depth = INT_MAX;
    if (root->left) {
        min_depth = fmin(minDepth(root->left), min_depth);
    }
    if (root->right) {
        min_depth = fmin(minDepth(root->right), min_depth);
    }

    return min_depth + 1;
}
