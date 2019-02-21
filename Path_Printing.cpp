#include<bits/stdc++.h>

using namespace std;
const int maxn = 101;
string s1 , s2 , s3;
int n , m , k , kk;
int dp[maxn][maxn][maxn];
int dp1[maxn][maxn][maxn];
int inf = -1e9;
bool vis[maxn];
int ar[maxn];

void KMP()
{
    int i=1,k=0;
    ar[0]=0;
    while(i<kk) {
        if(s3[i]==s3[k]) {
            ++k;
            ar[i]=k;
            i++;
        }
        else {
            if(k==0) {
                ar[i]=0;
                i++;
            }
            else {
                k=ar[k-1];
            }
        }
    }
}

int solve(int i , int j , int l){
    if(l >= k)return inf;
    if(i >= n || j  >= m)return 0;
    int &ret = dp[i][j][l];
    if(ret != -1)return ret;
    ret = inf;
    ret = max(solve(i+1,j,l), solve(i,j+1,l));
    ret = max(ret , solve(i+1,j+1,l));
    if(s1[i] == s2[j]){
        if(s1[i] == s3[l]){
            ret = max(ret , 1 + solve(i+1,j+1,l+1));
        }
        else{
            int tp = l;
            while(tp > 0 and s3[tp]!=(s1[i]))tp = ar[tp-1];
            if(s3[tp] == s1[i])tp++;
            ret = max(ret , 1 + solve(i+1,j+1,tp));
        }
    }
    return ret;
}
string ans = "";

void Print(int i , int j , int l){
    if(l >= k)return;
    if(i >= n || j  >= m)return;
    int ret = solve(i,j,l);
    if(ret == solve(i+1,j,l))Print(i+1,j,l);
    else if(ret == solve(i,j+1,l))Print(i,j+1,l);
    else if((s1[i] == s2[j])){
        if((s1[i] == s3[l]) and (ret == 1 + solve(i+1,j+1,l+1))){
            ans += s1[i];
            //cout << ret << " ";
            Print(i+1,j+1,l+1);
        }
        else{
            ans += s1[i];
            int tp = l;
            while(tp > 0 and s3[tp]!=(s1[i]))tp = ar[tp-1];
            if(s3[tp] == s1[i])tp++;
            Print(i+1,j+1,tp);
        }
    }
    else{
        cout << "NO way!";
    }
}

int main()
{
    cin >> s1 >> s2 >> s3;
    n = s1.size(); m = s2.size() ; k = s3.size();
    kk = k;
    KMP();
    memset(dp , -1 , sizeof dp);
    memset(dp1 , -1 , sizeof dp1);
    int ok = solve(0,0,0);
    //cout << ok << endl;
    Print(0,0,0);
   // reverse(ans.begin(),ans.end());
    if(ans.size() == 0)ans+='0';
    cout << ans << endl;
    return 0;
}
