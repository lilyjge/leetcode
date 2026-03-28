class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<int> starts;
        for(int i = 0; i < intervals.size(); i++)
            starts.push_back(intervals[i][0]);
        int idx = upper_bound(starts.begin(), starts.end(), newInterval[0]) - starts.begin();
        int sidx = idx - 1, eidx = idx - 1;
        vector<int> merged = newInterval;
        if (idx != 0) {
            vector<int> before = intervals[idx-1];
            if (newInterval[0] <= before[1]) {
                sidx = idx - 2;
                merged[0] = before[0];
            }
            else {
                sidx = idx - 1;
                merged[0] = newInterval[0];
            }
        }
        else {
            merged[0] = newInterval[0];
            eidx++;
        }
        cout << eidx << endl;
        while (eidx >= 0 && eidx < intervals.size() && newInterval[1] >= intervals[eidx][0]) {
            if (intervals[eidx][1] <= newInterval[1]) merged[1] = newInterval[1];
            else merged[1] = intervals[eidx][1];
            eidx++;
        }
        vector<vector<int>> updated;
        for(int i = 0; i <= sidx; i++) updated.push_back(intervals[i]);
        updated.push_back(merged);
        for(int i = eidx; i >= 0 && i < intervals.size(); i++) updated.push_back(intervals[i]);
        return updated;
    }
};
