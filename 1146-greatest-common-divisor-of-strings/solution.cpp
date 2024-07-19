class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        string gcd = "";
        string ns = "";
        for(int i = 0; i < min(str1.size(), str2.size()); i++){
            if(str1[i] == str2[i]){
                ns += str1[i];
                if(str1.size() % ns.size() == 0 && str2.size() % ns.size() == 0)
                    gcd = ns;
            }
            else{
                break;
            }
        }
        string check = "";
        if(gcd.size() == 0) return "";
        for(int i = 0; i < str1.size() / gcd.size(); i++)
            check += gcd;
        if(check != str1) return "";
        check = "";
        for(int i = 0; i < str2.size() / gcd.size(); i++)
            check += gcd;
        if(check != str2) return "";
        return gcd;
    }
};
