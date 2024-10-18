class Solution {
public:
    int fun(int index, vector<int> nums, int mx, int ans){
        index++; 
        if(index == nums.size()) return mx == ans;
        return fun(index, nums, max(mx, mx | nums[index]), ans) + fun(index, nums, mx, ans);
    }

    int countMaxOrSubsets(vector<int>& nums) {
        int mx = nums[0];
        for(int i = 0; i < nums.size(); i++){
            mx = max(mx, mx | nums[i]);
        }
        return fun(-1, nums, 0, mx);
    }
};
