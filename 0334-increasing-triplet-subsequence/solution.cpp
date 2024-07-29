class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int small = nums[0], big = nums[nums.size() - 1];
        vector<int> smalls(nums.size()), bigs(nums.size());
        for(int i = 0; i < nums.size(); i++){
            small = min(small, nums[i]);
            smalls[i] = small;
        }
        for(int i = nums.size() - 1; i >= 0; i--){
            big = max(big, nums[i]);
            bigs[i] = big;
        }
        for(int i = 0; i < nums.size(); i++)
            if(nums[i] > smalls[i] && nums[i] < bigs[i])
                return true;
        return false;
    }
};
