class Solution {
public:
    string reverseWords(string s) {
        string ans = "";
        int i = s.length() - 1;
        string word = "";
        bool inword = false;
        while(i >= 0){
            if(s[i] != ' ') word = s[i] + word;
            else if(word != ""){
                ans += word + " ";
                word = "";
            } 
            i--;
        }
        if(word != "") ans += word;
        else ans = ans.substr(0, ans.length() - 1);
        return ans;
    }
};
