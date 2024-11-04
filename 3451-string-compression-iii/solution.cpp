class Solution {
public:
    string compressedString(string word) {
        string comp = "";
        int cnt = 1; char cur = word[0];
        int n = word.size();
        for(int i = 1; i < n; i++){
            if(cnt >= 9 || cur != word[i] && cnt != 0){
                comp += to_string(cnt);
                comp += cur;
                cur = word[i];
                cnt = 1;
            }
            else cnt++;
        }
        if(cnt != 0){
            comp += to_string(cnt);
            comp += cur;
        }
        if(word.size() == 1) comp = to_string(1) + word;
        return comp;
    }
};
