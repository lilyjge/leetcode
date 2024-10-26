class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int ans = 0, cur = 0, canflip = 1;
        for(int l = 0, r = 0; r < nums.size(); r++){
            if(nums[r]) cur++;
            else{
                if(canflip){
                    canflip--;
                }
                else{
                    while(nums[l] && l < r){
                        l++;
                        cur--;
                    }
                    if(!nums[l]){
                        l++;
                    }
                }
            }
            ans = max(cur, ans);
        }
        if(canflip) ans--;
        return ans;
    }
};
