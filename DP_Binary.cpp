#include<bits/stdc++.h>

using namespace std;
const int maxn = 3e5+10;
int dp[maxn] , pre[maxn] , a[maxn];
int n , k;


int sum(int x , int y){
    if(x > y) return 0;
    if(x == 0)return pre[y];
    else      return pre[y] - pre[x-1];
}

int good(int x){
    int l = 1;
    dp[0] = pre[0] = 1;
    for(int r = 1; r <=n ; r++){
        while(l < r and a[r]-a[l] > x){
            ++l;
        }
        int opt1 = l - 1;
        int opt2 = r - k;
        if(sum(opt1,opt2) > 0){
            dp[r] = 1;
        }
        else
            dp[r] = 0;
        pre[r] = pre[r-1] + dp[r];
    }
    cout << x << " : " ;
    for(int i = 1; i<=n; i++){
        cout << dp[i] << " ";
    }
    cout << endl;
    cout << "pre " << x << " : ";
    for(int i = 1; i<=n; i++){
        cout << pre[i] << " ";
    }
    cout << endl;
    return dp[n];
}



int search(int b , int e){
    if(b == e)return b;
    int m = ( b + e ) >> 1;
    if(good(m))return search(b , m);
    else return search(m+1,e);
}


int main()
{
    scanf("%d%d",&n,&k);
    for(int i = 1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    printf("%d\n",search(0,1000000000));
    return 0;
}
