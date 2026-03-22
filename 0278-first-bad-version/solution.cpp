// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int mi = 1;
        int mx = n;
        while(mi < mx) {
            int md = (long)((long)mi + (long)mx) / 2;
            if (isBadVersion(md)) mx = md;
            else mi = md + 1;
        }
        return mi;
    }
};
