class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        sort(folder.begin(), folder.end());
        unordered_set<string> uniques;
        for(int i = 0; i < folder.size(); i++){
            string cur = folder[i];
            string f = "/"; bool good = true;
            for(int j = 1; j < cur.length(); j++){
                if(cur[j] == '/'){
                    if(uniques.find(f) != uniques.end()){
                        good = false;
                        break;
                    }
                }
                f += cur[j];
            }
            if(good) uniques.insert(f); 
        }
        vector<string> ans;
        for(string s : uniques){
            ans.push_back(s);
        }
        return ans;
    }
};
