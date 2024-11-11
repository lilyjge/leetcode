class Solution {
public:
    bool primeSubOperation(vector<int>& nums) {
        vector<bool> composite(1001);
        vector<int> primes;
        primes.push_back(0);
        for(int i = 2; i <= 1000; i++){
            if(!composite[i]){
                int j = 2 * i;
                while(j <= 1000){
                    composite[j] = true;
                    j += i;
                }
                primes.push_back(i);
            }
        }
        for(int i = 0; i < nums.size(); i++){
            int cur = nums[i];
            int diff = nums[i];
            if(i != 0) diff = nums[i] - nums[i-1];
            if(diff <= 0) return false;
            int upper = lower_bound(primes.begin(), primes.end(), cur) - primes.begin() - 1;
            if(upper < 0 || upper >= primes.size()) return false;
            cout << "upper: " << primes[upper] << " diff: " << diff << endl;
            while(upper >= 0 && primes[upper] >= diff) upper--;
            if(upper < 0) return false;
            nums[i] -= primes[upper];
            cout << "num: " << nums[i] << endl;
            if(i != 0 && nums[i] <= nums[i-1]) return false;
        }
        return true;
    }
};
