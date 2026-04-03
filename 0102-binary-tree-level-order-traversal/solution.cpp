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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> order;
        queue<pair<int, TreeNode*>> q;
        q.push({0, root});
        while(!q.empty()) {
            auto e = q.front(); q.pop();
            if (e.second == nullptr) continue;
            if (order.size() <= e.first) 
                order.push_back({});
            order[e.first].push_back(e.second->val);
            q.push({e.first + 1, e.second->left});
            q.push({e.first + 1, e.second->right});
        }     
        return order;
    }
};
