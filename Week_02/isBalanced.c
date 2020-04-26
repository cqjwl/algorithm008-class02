#include <stdio.h>
#include <stdlib.h>
#include "isBalanced.h"

int maxDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }

    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    return fmax(leftDepth, rightDepth) + 1;
}

bool isBalanced(struct TreeNode* root){
    if(root == NULL) {
        return true;
    }

    int left = maxDepth(root->left);
    int right = maxDepth(root->right);

    return (left - right > -2 && left - right < 2 && 
            isBalanced(root->left) && isBalanced(root->right)); 

}
