///https://www.youtube.com/watch?v=UUkazajFDmc&list=RDUUkazajFDmc&start_radio=1
#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define dbug printf("I am here\n");
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int maxn = 5e6+100;
/* 1 base hashing */
const ll inf = 1e18;
const ll base1 = 31;
const ll base2 = 53;
ll mod1 = 1e9 + 9;
ll mod2 = 1e9 + 7;
ll F1[maxn] , L1[maxn] , R1[maxn];
ll F2[maxn] , L2[maxn] , R2[maxn];
char in[maxn];
int n , dp[maxn];

/// p(hs) should near the total number of character and prime
/// First hash value must not use as Zero like in[0] > 0
/// Hash equation hash(s) = s[0]+s[1]*p+s[2]*p2+...+s[n−1]*p n−1 mod m=∑i=0 to n−1 s[i]*p^i mod m.


pair<ll,ll> seg(int x , int y){
    ll f = ((L1[y]-L1[x-1])*F1[n-y])%mod1;
    ll s = ((L2[y]-L2[x-1])*F2[n-y])%mod2;
    return make_pair(f,s);
}

pair<ll,ll> seg2(int x , int y){
    ll f = ((R1[x]-R1[y+1]+mod1)*F1[x-1])%mod1;
    ll s = ((R2[x]-R2[y+1]+mod2)*F2[x-1])%mod2;
    return make_pair(f,s);
}

bool palindrome(int x , int y){
    return seg(x,y)==seg2(x,y);
}

void build_double_Hashing(){
    F1[0] = 1;
    F2[0] = 1;
    for(int i = 1; i<maxn; i++)F1[i] = F1[i-1]*base1;
    for(int i = 1; i<maxn; i++)F2[i] = F2[i-1]*base2;
    for(int i = 1; i<=n; i++)L1[i] = (L1[i-1] + in[i]*F1[i-1])%mod1;
    for(int i = 1; i<=n; i++)L2[i] = (L2[i-1] + in[i]*F2[i-1])%mod2;
    for(int i = n; i>=1; i--)R1[i] = (R1[i+1] + in[i]*F1[n-i])%mod1;
    for(int i = n; i>=1; i--)R2[i] = (R2[i+1] + in[i]*F2[n-i])%mod2;
}


int main()
{
    fast;
    cin >> (in+1);
    n = strlen(in+1);
    build_double_Hashing();
    while(1){
        ll l , r;
        cin >> l >> r;
        cout << seg(l,r).first << " " << seg(l,r).second << endl;
        cout << seg2(l,r).first << " " << seg2(l,r).second << endl;
        cout << endl;
    }
}
/*



*/



