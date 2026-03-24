class Solution {
public:
    string addBinary(string a, string b) {
        string ans = "";
        int i = a.length() - 1, j = b.length() - 1;
        int carry = 0;
        while(i >= 0 && j >= 0) {
            int dig1 = a[i] - '0', dig2 = b[j] - '0';
            char c = ' ';
            int cum = dig1 + dig2 + carry;
            if (cum == 0 || cum == 1) {
                c = cum + '0';
                carry = 0;
            }
            else {
                carry = 1;
                if (cum == 2) c = '0';
                else c = '1';
            }
            ans = c + ans;
            // cout << dig1 << " " << dig2 << " " << cum << " " << carry << " " << ans << endl;
            i--;
            j--;
        }
        while (i >= 0) {
            int dig = a[i] - '0';
            int cum = dig + carry;
            char c = ' ';
            if (cum == 0 || cum == 1) {
                carry = 0;
                c = cum + '0';
            } else {
                carry = 1;
                c = '0';
            }
            ans = c + ans;
            // cout << dig << " " << cum << " " << carry << " " << c << " " << ans << endl;
            i--;
        }
        while (j >= 0) {
            int dig = b[j] - '0';
            int cum = dig + carry;
            char c = ' ';
            if (cum == 0 || cum == 1) {
                carry = 0;
                c = cum + '0';
            } else {
                carry = 1;
                c = '0';
            }
            ans = c + ans;
            // cout << dig << " " << cum << " " << carry << " " << c << " " << ans << endl;
            j--;
        }
        if (carry ) ans = '1' + ans;
        return ans;
    }
};
