class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zeroes = 0;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] == 0) zeroes++;
            else{
                nums[i - zeroes] = nums[i];
                if(zeroes != 0)nums[i] = 0;
            }
        }
    }
};
