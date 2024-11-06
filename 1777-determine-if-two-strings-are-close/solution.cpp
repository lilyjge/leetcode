class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size()) return false;
        unordered_map<int, int> cnt1, cnt2, count;
        for(int i = 0; i < word1.size(); i++)
            cnt1[word1[i]]++;
        for(int i = 0; i < word2.size(); i++){
            if(cnt1.find(word2[i]) == cnt1.end()) return false;
            cnt2[word2[i]]++;
        }
        for(auto e : cnt2){
            count[e.second]++;
        }
        for(auto e : cnt1){
            if(count.find(e.second) == count.end() || count[e.second] == 0) return false;
            count[e.second]--;
        }
        return true;
    }
};
