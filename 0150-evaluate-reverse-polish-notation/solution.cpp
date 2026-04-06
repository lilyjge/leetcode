class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        int res;
        for(string t : tokens) {
            if (isdigit(t[t.length() - 1])) {
                // cout << "pushing " << t << endl;
                s.push(stoi(t));
                continue;
            }
            // cout << "operating " << t << endl;
            int second = s.top(); s.pop();
            // cout << "second " << second << endl;
            int first = s.top(); s.pop();
            // cout << "firt " << first << endl;
            if (t == "+") res = first + second;
            else if (t == "-") res = first - second;
            else if (t == "*") res = first * second;
            else if (t == "/") res = first / second;
            s.push(res);
        } 
        return s.top();
    }
};
