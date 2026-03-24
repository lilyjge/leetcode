class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> appears;
        for(int i = 0; i < s.length(); i++) {
            appears[s[i]]++;
        }
        int ans = 0;
        bool odd = false;
        for(auto pi : appears) {
            if (pi.second % 2 == 0) ans += pi.second;
            else{ 
                if (!odd) {
                    ans++;
                    odd = true;
                }
                ans += pi.second - 1;
            }
        }
        return ans;
    }
};
