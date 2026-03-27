/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        // at each node the diameter of the subtree is the diameter of left + dia of right
        // its 'contribution' to parents is max(leftD, rightD) + 1
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 0;
        return max(height(root->left) + height(root->right), 
            max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)));
    }

    int height(TreeNode* root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 1;
        return max(height(root->left), height(root->right)) + 1;
    }
};
