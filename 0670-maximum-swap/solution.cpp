class Solution {
public:
    int maximumSwap(int num) {
        string str = to_string(num);
        int ans = num;
        for(int i = 0; i < str.length(); i++){
            for(int j = i + 1; j < str.length(); j++){
                string cur = str;
                cur[i] = str[j];
                cur[j] = str[i];
                if(stoi(cur) > ans)
                    ans = stoi(cur);
            }
        }
        return ans;
    }
};
