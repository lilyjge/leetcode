class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        for(int i = 0; i < nums.size(); i++){
            int cur = nums[i];
            int index = upper_bound(nums.begin(), nums.end(), k - cur) - nums.begin() - 1;
            if(index <= i) break;
            if(cur + nums[index] != k) continue;
            nums.erase(nums.begin() + index);
            ans++;
        }
        return ans;
    }
};
