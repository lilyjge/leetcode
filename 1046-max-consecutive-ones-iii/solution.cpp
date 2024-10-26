class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int ans = 0, cur = 0;
        for(int l = 0, r = 0; r < nums.size(); r++){
            if(nums[r]) cur++;
            else{
                if(k > 0){
                    k--;
                    cur++;
                }
                else{
                    if(nums[l]){
                        while(nums[l] && l < r){
                            l++; cur--;
                        }
                        if(!nums[l]) l++;
                    }
                    else{
                        l++;
                    }
                }
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};
