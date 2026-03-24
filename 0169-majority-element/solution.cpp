class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans = 1e9 + 3; 
        int cnt = 0;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] != ans) {
                cnt--;
                if (cnt <= 0) {
                    ans = nums[i];
                    cnt = 1;
                }
            }
            else cnt++;
        }
        return ans;
    }
};
