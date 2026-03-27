class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> unique;
        for(int i = 0; i < nums.size(); i++)
            unique.insert(nums[i]);
        return nums.size() != unique.size();
    }
};
