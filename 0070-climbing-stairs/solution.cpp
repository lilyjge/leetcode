class Solution {
public:
    int steps[46] = {};
    int climbStairs(int n) {
        if (steps[n] != 0) return steps[n];
        if (n == 1 || n == 0) return 1;
        steps[n] = climbStairs(n - 2) + climbStairs(n - 1);
        return steps[n];
    }
};
