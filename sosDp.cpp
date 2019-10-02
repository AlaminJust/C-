/// Sos dp ///
#include<bits/stdc++.h>

using namespace std;

int arr[1<<20];
int dp[1<<20][20];

int main()
{
    string s;
    cin >> s;
    int len = s.size();
    for(int j = 0; j<len; j++){
        int mask = 0;
        for(int k = j; k<len; k++){
            int bit = s[k]-'a';
            if(mask&(1<<bit))break;
            mask |= (1<<bit);
            arr[mask] = __builtin_popcount(mask);
        }
    }

    for(int mask = 0; mask < (1<<20); mask++){
        for(int j = 0; j<20; j++){
            if(j == 0){
                dp[mask][j] = arr[mask];
                if(mask & (1<<j))
                    dp[mask][j] = max(dp[mask][j] , arr[mask ^ (1<<j)]);
            }
            else{
                dp[mask][j] = max(dp[mask][j] , dp[mask][j-1]);
                if(mask & (1 << j)){
                    dp[mask][j] = max(dp[mask][j] , dp[mask ^ (1<<j)][j-1]);
                }
            }
        }
    }

    int ans = 0;
    for(int mask = 0; mask < (1<<20); mask++){
        ans = max(ans , dp[mask][19] + dp[((1<<20)-1) - mask][19]);
    }
    cout << ans << endl;
    return 0;
}
