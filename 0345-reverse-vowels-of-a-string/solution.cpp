class Solution {
public:
    string reverseVowels(string s) {
        int i = 0, j = s.size() - 1;
        unordered_set<char> vowels;
        vowels.insert('a');
        vowels.insert('e');
        vowels.insert('i');
        vowels.insert('o');
        vowels.insert('u');
        vowels.insert('A');
        vowels.insert('E');
        vowels.insert('I');
        vowels.insert('O');
        vowels.insert('U');
        while(i < j){
            while(vowels.find(s[i]) == vowels.end() && i < s.size() && i < j)
                i++;
            //cout << "vowel: " << s[i] << "\n";
            while(vowels.find(s[j]) == vowels.end() && j > 0 && i < j)
                j--;
            //cout << "vowel: " << s[j] << "\n";   
            if(i >= j) break;
            char t = s[i];
            s[i] = s[j];
            s[j] = t;
            i++;
            j--;
        }
        return s;
    }
};
