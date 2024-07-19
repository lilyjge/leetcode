class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string w = "";
        int l = min(word1.length(), word2.length());
        for(int i = 0; i < l; i++){
            //w += word1[i] + word2[i];
            w = w + word1[i];
            w = w + word2[i];
        }
        w += word1.substr(l);
        w += word2.substr(l);
        return w;
    }
};
