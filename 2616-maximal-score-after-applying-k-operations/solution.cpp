class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int> q;
        for(int n : nums)
            q.push(n);
        long long sum = 0;
        for(int i = 0; i < k; i++){
            int c = q.top();
            q.pop();
            q.push(ceil(c / 3.0));
            sum += c;
        }
        return sum;
    }
};
