class Solution {
public:
    bool isPalindrome(string s) {
        string str = "";
        for(int i = 0; i < s.length(); i++) {
            if (isalnum(s[i])) {
                str += tolower(s[i]);
            }
        }
        for(int i = 0; i < min(str.length() / 2 + 1, str.length()); i++) {
            if (str.length() - i - 1 < 0) {
                continue;
            }
            if(str[i] != str[str.length() - i - 1]) {
                return false;
            }
        } 
        return true;
    }
};
