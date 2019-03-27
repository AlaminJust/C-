#include<bits/stdc++.h>

using namespace std;
const int maxn = 1e5+100;
int Z[maxn]; /// Z will store length of the longest substring which is also prefix.

void getZarr(string str){
    int n = str.size();
    int L , R , k;
    L = R = 0;
    for(int i = 1; i<n; i++){
        if(i > R){
            L = R = i;
            while(R < n and str[R-L] == str[R])
                R++;
            Z[i] = R - L;
            R--;
        }
        else{
            k = i - L;
            if(Z[k] < (R - i + 1))
                Z[i] = Z[k];
            else{
                L = i;
                while(R < n and str[R - L] == str[R])
                    R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
}

void search(string text , string pattern){
    string concat = pattern + "$" + text;
    int l = concat.size();
    getZarr(concat);
    for(int i = 0; i<l; i++){
        if(Z[i] == pattern.size()){
            cout << "Pattern found at index "
                << i - pattern.size()-1 << endl;
        }
    }
}


int main()
{
    string text = "GEEKS FOR GEEKS";
    string pattern = "GEEKS";
    search(text, pattern);
    return 0;
}
