class Solution {
public:
    int mySqrt(int x) {
        long long i = 0;
        while(i <= x){
            if(i * i > x) break;
            i++;
        }
        return (int)i - 1;
    }
};
