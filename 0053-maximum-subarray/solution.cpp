class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0];
        int cur = 0;
        for(int i = 0; i < nums.size(); i++) {
            cur = max(cur + nums[i], nums[i]);
            ans = max(ans, cur);
        }
        return ans;
    }
};
