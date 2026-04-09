class Trie {
public:
        unordered_set<string> words;
        unordered_set<string> prefixes;
    Trie() {

    }
    
    void insert(string word) {
        for(int i = 1; i <= word.length(); i++) 
            prefixes.insert(word.substr(0, i));
        words.insert(word);
    }
    
    bool search(string word) {
        return words.contains(word);
    }
    
    bool startsWith(string prefix) {
        return prefixes.contains(prefix);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
