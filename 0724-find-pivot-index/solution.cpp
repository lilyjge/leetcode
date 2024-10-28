class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        vector<int> psa(1);
        for(int i = 0; i < nums.size(); i++){
            psa.push_back(psa[i] + nums[i]);
        }
        int ans = -1;
        for(int i = 1; i < nums.size(); i++){
            int left = psa[i -1];
            int right = psa[nums.size()] - psa[i];
            cout << "left: " << left << " right: " << right << endl;
            if(left == right){
                ans = i - 1;
                break;
            }
        }
        if(ans == -1){
            if(psa[nums.size()] - psa[1] == 0) ans = 0;
            else if(psa[nums.size() - 1] == 0) ans = nums.size() - 1;
        }
        return ans;
    }
};
