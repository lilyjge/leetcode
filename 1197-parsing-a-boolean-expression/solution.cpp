class Solution {
public:
    bool fun(string s){
        if(s == "f") return false;
        if(s == "t") return true;
        char op = s[0];
        string rem = s.substr(2, s.length() - 3);
        if(op == '!')
            return !fun(rem);
        bool good; 
        if(op == '&') good = true;
        else good = false;
        int inexp = 0;
        string nxt = "";
        for(int i = 0; i < rem.length(); i++){
            if(rem[i] == '(') inexp--;
            if(rem[i] == ')') inexp++;
            if(rem[i] == ',' && inexp == 0){
                if(op == '&') good = good && fun(nxt);
                else good = good || fun(nxt);
                nxt = "";
            }
            else if(i == rem.length() - 1){
                nxt += rem[i];
                if(op == '&') good = good && fun(nxt);
                else good = good || fun(nxt);
                nxt = "";
            }
            else{
                nxt += rem[i];
            }
        }
        return good;  
    }

    bool parseBoolExpr(string expression) {
        return fun(expression);
    }
};
