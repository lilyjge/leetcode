class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> pre(nums.size());
        pre[0] = nums[0];
        for(int i = 1; i < nums.size(); i++) 
            pre[i] = nums[i] * pre[i - 1];
        int prod = 1;
        for(int i = nums.size() - 1; i > 0; i--) {
            pre[i] = pre[i - 1] * prod;
            prod *= nums[i];
        }
        pre[0] = prod;
        return pre;
    }
};
