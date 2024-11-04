class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s1, s2;
        for(int i = 0; i < nums1.size(); i++){
            s1.insert(nums1[i]);
        }
        for(int i = 0; i < nums2.size(); i++){
            s2.insert(nums2[i]);
        }
        vector<vector<int>> ans(2);
        for(int a : s1){
            if(s2.find(a) == s2.end())
                ans[0].push_back(a);
        }
        for(int a : s2){
            if(s1.find(a) == s1.end())
                ans[1].push_back(a);
        }
        return ans;
    }
};
