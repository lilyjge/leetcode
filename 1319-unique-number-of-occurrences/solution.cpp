class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> mp;
        for(int i = 0; i < arr.size(); i++){
            mp[arr[i]]++;
        }
        unordered_set<int> cnts;
        for(auto e : mp){
            int c = e.second;
            if(cnts.find(c) != cnts.end()) 
                return false;
            cnts.insert(c);
        }
        return true;
    }
};
