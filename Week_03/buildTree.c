#include <stdio.h>
#include <stdlib.h>
#include "buildTree.h"

void helper(int* preorder, int* inorder, int treeSize, struct TreeNode* root){
    int leftCnt = 0;
    int rightCnt = 0;
    for (int i = 0; i < treeSize; i++) {
        if (root->val == inorder[i]) {
            break;
        } else {
            leftCnt++;
        }
    }

    if (leftCnt) {
        struct TreeNode* leftNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        leftNode->val = preorder[1];
        leftNode->left = NULL;
        leftNode->right = NULL;
        root->left = leftNode;
        helper(preorder + 1, inorder, leftCnt, root->left);
    }

    rightCnt = treeSize - leftCnt - 1;
    if (rightCnt) {
        struct TreeNode* rightNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        rightNode->val = preorder[leftCnt + 1];
        rightNode->left = NULL;
        rightNode->right = NULL;
        root->right = rightNode;
        helper(preorder + leftCnt + 1, inorder + leftCnt + 1, rightCnt, root->right);
    }

    return;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    if (preorder == NULL || preorderSize <= 0 || 
        inorder == NULL || inorderSize <= 0 || 
        preorderSize != inorderSize) {
        return NULL;
    }

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    root->left = NULL;
    root->right = NULL;

    helper(preorder, inorder, preorderSize, root);

    return root;
}
