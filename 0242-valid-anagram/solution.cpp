class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> cnts, cntt;
        if(s.length() != t.length()) return false;
        for(int i = 0; i < s.length(); i++) {
            cnts[s[i]]++;
            cntt[t[i]]++;
        }
        if(cnts.size() != cntt.size()) return false;
        for(auto pi: cnts) {
            if(cntt[pi.first] != pi.second) return false;
        }
        return true;
    }
};
