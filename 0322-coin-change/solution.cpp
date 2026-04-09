class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int INTMAX = 1e4 + 2;
        vector<int> nums(amount + 1, INTMAX);
        nums[0] = 0;
        for(int i = 1; i <= amount; i++) {
            // cout << "amount " << i << endl;
            for (int c : coins) {
                if (c > i || nums[i - c] == INTMAX) continue;
                // cout << "coin " << c << endl;
                nums[i] = min(nums[i - c] + 1, nums[i]);
                // cout << "res " << nums[i] << endl;
            }
        }
        if (nums[amount] == INTMAX) return -1;
        return nums[amount];
    }
};
