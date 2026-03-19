class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto itr = upper_bound(nums.begin(), nums.end(), target);
        int idx = itr - nums.begin() - 1;
        if (idx < 0) return -1;
        if (nums[idx] == target) return idx;
        return -1;
    }
};
