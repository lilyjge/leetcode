class Solution {
public:
    int longestSubsequence(string s, int k) {
        int zeroes = 0, ones = 0, cnt = 0;
        for(int i = 0; i < s.size(); i++){
            if (s[i] == '0')
                zeroes++;
            if (s[s.size() - 1 - i] == '1'){
                if (cnt > k) continue;
                if(pow(2, i) > INT_MAX){
                    cnt = k + 1; continue;
                }
                int dig = (int) pow(2, i);
                if (dig + cnt <= k){
                    cnt += dig;
                    ones++;
                }
                else{
                    cnt = k + 1;
                }
            }
        }
        return zeroes + ones;
    }
};
