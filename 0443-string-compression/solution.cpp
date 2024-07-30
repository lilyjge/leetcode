class Solution {
public:
    int compress(vector<char>& chars) {
        int curchanged = 0;
        char cur = chars[0];
        int cnt = 1;
        if(chars.size() == 1) return 1;
        for(int i = 1; i < chars.size(); i++){
            if(chars[i] != cur){
                chars[curchanged] = cur;
                curchanged++;
                if(cnt > 1){
                    string c = to_string(cnt);
                    for(int j = 0; j < c.size(); j++){
                        chars[curchanged] = c[j];
                        curchanged++;
                    }
                }
                cnt = 1;
                cur = chars[i];
            }
            else{
                cnt++;
            }
            if(i == chars.size() - 1){
                chars[curchanged] = cur;
                curchanged++;
                if(cnt > 1){
                    string c = to_string(cnt);
                    for(int j = 0; j < c.size(); j++){
                        chars[curchanged] = c[j];
                        curchanged++;
                    }
                }
            }
        }
        return curchanged;
    }
};
