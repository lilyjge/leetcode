class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        if(x < 0) s = "-" + s;
        for(int i = 0; i < s.size() / 2; i++){
            if(s[i] != s[s.size() - i - 1]) return false;
        }
        return true;
    }
};
