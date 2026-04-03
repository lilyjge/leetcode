class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_map<int, int> cnts;
        for(int i = 0; i < nums.size(); i++) 
            cnts[nums[i]]++;
        vector<vector<int>> ans;
        for(auto e : cnts) {
            int i = e.first, cnt = e.second;
            if (i == 0 && cnt >= 3) ans.push_back({i, i, i});
            if (cnt >= 2) {
                int leftover = 0 - 2 * i;
                if (leftover > i && cnts.contains(leftover))
                    ans.push_back({i, i, leftover});
            }
            for(auto f : cnts) {
                if (f.first <= i) continue;
                int leftover = 0 - i - f.first;
                if (leftover <= i || leftover < f.first) continue;
                if (leftover == f.first && f.second >= 2) 
                    ans.push_back({i, f.first, f.first});
                else if (leftover != f.first && cnts.contains(leftover))
                    ans.push_back({i, f.first, leftover});
            }
        }
        return ans;
    }
};
