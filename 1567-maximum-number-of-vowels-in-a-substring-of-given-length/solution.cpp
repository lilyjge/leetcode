class Solution {
public:
    bool isvowel(char ch) { return (ch == 'a') || (ch == 'e') ||(ch == 'i') ||(ch == 'o') ||(ch == 'u'); }

    int maxVowels(string s, int k) {
        int ans = 0;
        for(int i = 0; i < k; i++)
            if(isvowel(s[i]))
                ans++;
        int cnt = ans;
        for(int l = 1, r = k; r < s.length(); l++, r++){
            // cout << cnt << endl;
            char prev = s[l-1];
            char cur = s[r];
            if(isvowel(prev)) cnt--;
            if(isvowel(cur)) cnt++;
            ans = max(ans, cnt);
        }
        return ans;
    }
};
