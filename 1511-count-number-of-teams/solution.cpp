class Solution {
public:
    int numTeams(vector<int>& rating) {
        int ans = 0;
        for(int i = 0; i < rating.size(); i++){
            int one = rating[i];
            for(int j = i + 1; j < rating.size(); j++){
                int two = rating[j];
                for(int k = j + 1; k < rating.size(); k++){
                    int three = rating[k];
                    if(one > two && two > three || one < two && two < three)
                        ans++;
                }
            }
        }
        return ans;
    }
};
