class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        for(int i = 0; i < nums.size(); i++){
            int n = nums[i];
            if(mp.find(target - n) != mp.end()){
                vector<int> ans;
                ans.push_back(i);
                ans.push_back(mp[target - n]);
                return ans;
            }
            else{
                mp[n] = i;
            }
        }
        return nums;
    }
};
