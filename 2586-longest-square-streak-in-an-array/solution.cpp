class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int cnt = 0;
        for(int i = 0; i < nums.size(); i++){
            long long cur = nums[i];
            int len = 1;
            long long sq = cur * cur;
            while(sq <= nums[nums.size()-1]){
                int nxt = upper_bound(nums.begin(), nums.end(), sq) - nums.begin() - 1;
                cout << "cur: " << cur << " nxt: " << nxt << endl; 
                if(sq != nums[nxt]) break;
                len++;
                sq = sq * sq;
            }
            if(len != 1) cnt = max(cnt, len);
        }
        if(cnt == 0) cnt = -1;
        return cnt;
    }
};
