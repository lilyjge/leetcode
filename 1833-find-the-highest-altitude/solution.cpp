class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int cur = 0, ans = 0;
        for(int i = 0; i < gain.size(); i++){
            cur += gain[i];
            ans = max(cur, ans);
        }
        return ans;
    }
};
