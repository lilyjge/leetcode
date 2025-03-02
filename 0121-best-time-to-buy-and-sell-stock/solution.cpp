class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> mi(n);
        vector<int> mx(n);
        mi[0] = prices[0];
        mx[n-1] = prices[n-1];
        for(int i = 1; i < n; i++){
            mi[i] = min(prices[i], mi[i-1]);
            mx[n - i - 1] = max(prices[n - i - 1], mx[n - i]);
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            // cout << i << " " << mx[i] << " " << mi[i] << endl;
            ans = max(ans, mx[i] - mi[i]);
        }
        return ans;
    }
};
