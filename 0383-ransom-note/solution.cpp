class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> available;
        for(int i = 0; i < magazine.length(); i++) {
            available[magazine[i]]++;
        }
        for(int i = 0; i < ransomNote.length(); i++) {
            if (available[ransomNote[i]] == 0) return false;
            available[ransomNote[i]]--;
        }
        return true;
    }
};
