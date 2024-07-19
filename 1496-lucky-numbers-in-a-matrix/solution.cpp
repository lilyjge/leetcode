class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        vector<int> nums;
        for(int i = 0; i < matrix.size(); i++){
            int lowi = 0, lowest = matrix[i][0];
            for(int j = 0; j < matrix[i].size(); j++){
                if(matrix[i][j] < matrix[i][lowi]){
                    lowest = matrix[i][j];
                    lowi = j;
                }
            }
            int highi = i, highest = matrix[i][lowi];
            for(int j = 0; j < matrix.size(); j++){
                if(matrix[j][lowi] > highest){
                    highest = matrix[j][lowi];
                    highi = j;
                }
            }
            if(highest == lowest) nums.push_back(highest);
        }
        return nums;
    }
};
