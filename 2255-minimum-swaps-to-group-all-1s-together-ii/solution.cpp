class Solution {
public:
    int minSwaps(vector<int>& nums) {
        vector<int> two(nums.size() * 2);
        for(int i = 0; i < nums.size(); i++)
            two[i] = nums[i];
        for(int i = nums.size(); i < nums.size() * 2; i++)
            two[i] = nums[i - nums.size()];
        int ones = 0;
        for(int i = 0; i < nums.size(); i++)
            if(nums[i] == 1)
                ones++;
        int zeroes = 0;
        for(int i = 0; i < ones; i++)
            if(nums[i] == 0)
                zeroes++;
        int ans = zeroes;
        if(ones == 0) ans = 0;
        for(int i = 1, j = i + ones - 1; j < two.size(); i++, j++){
            if(two[i - 1] == 0 && two[j] == 1) zeroes--;
            if(two[i - 1] == 1 && two[j] == 0) zeroes++;
            ans = min(ans, zeroes);
            //cout << ans << endl;
        }
        return ans;
    }
};
