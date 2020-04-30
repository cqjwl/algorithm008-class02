#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lowestCommonAncestor.h"

bool helper(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q, struct TreeNode** result) {
    if (root == NULL) {
        return false;
    }

    int cnt = 0;
    if (helper(root->left, p, q, result)) {
        cnt++;
    }

    if (helper(root->right, p, q, result)) {
        cnt++;
    }

    if (root == p || root == q) {
        cnt++;
    }

    if (cnt >= 2) {
        result[0] = root;
    }

    if (cnt > 0) {
        return true;
    }

    return false;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode* result = NULL;
    helper(root, p, q, &result);
    return result;
}
