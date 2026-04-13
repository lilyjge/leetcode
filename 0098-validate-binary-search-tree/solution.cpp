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
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        return isSmaller(root->left, root->val) && isBigger(root->right, root->val);
    }

    bool isSmaller(TreeNode* root, int comp) {
        if (root == nullptr) return true;
        if (root->val >= comp) return false;
        // if (root->left == nullptr && root->right == nullptr) 
        //     return root->val < comp;
        return isSmaller(root->left, root->val) && isSmaller(root->right, comp) && isBigger(root->right, root->val);
    }

    bool isBigger(TreeNode* root, int comp) {
        if (root == nullptr) return true;
        if (root->val <= comp) return false;
        // if (root->left == nullptr && root->right == nullptr) 
        //     return root->val > comp;
        return isBigger(root->right, root->val) && isBigger(root->left, comp) && isSmaller(root->left, root->val);
    }
};
