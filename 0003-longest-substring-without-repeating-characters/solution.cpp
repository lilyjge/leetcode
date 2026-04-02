class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> seen;
        int ans = 0, front = 0, cur = 0;
        for(int i = 0; i < s.length(); i++) {
            // cout << "cur " << s[i] << " ans " << ans << " cur " << cur <<  endl;
            if(seen.contains(s[i])) {
                front = max(seen[s[i]] + 1, front);
                cur = i - front + 1;
                seen[s[i]] = i;
            }
            else {
                seen[s[i]] = i;
                cur++;
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};
