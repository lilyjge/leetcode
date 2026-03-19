class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for(int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c == '(' || c == '[' || c == '{') {
                stk.push(c);
            }
            else if (stk.empty()) {
                return false;
            }
            else if (c == ')' && stk.top() == '(' || c == ']' && stk.top() == '[' || c == '}' && stk.top() == '{') {
                stk.pop();
            }
            else {
                return false;
            }
        }
        return stk.empty();
    }
};
