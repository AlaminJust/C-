///https://www.youtube.com/watch?v=vOIqVQ76Iug
#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define dbug printf("I am here\n");
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int maxn = 2e6+100;

const ll inf = 1e18;
ll mod = 1e9+7;
ll fact[maxn] , factInv[maxn];

void factO(){
    fact[0] = 1;
    for(int i = 1; i<maxn; i++){
        fact[i] = (i*fact[i-1])%mod;
    }
    factInv[0] = factInv[1] = 1;
    ll p = mod;
    for(int i = 2; i<maxn; i++){
        factInv[i] = (p - (p/i) * factInv[p%i] % p) % p;
    }
    for(int i = 2; i<maxn; i++){
        factInv[i] *= factInv[i-1];
        factInv[i] %= mod;
    }
}

int main()
{
    factO();
    fast;
    int t; cin >> t;
    while(t--){
        ll n , m , q;
        cin >> n >> m >> q;
        ll ans = 0;
        ll x , y , p;
        for(int i = 0; i<q; i++){
            cin >> x >> y >> p;
            ll a = (x + y - 2);
            ll b = x - 1; ll c = y - 1;
            ll ans1 = (fact[a] * ((factInv[b])*(factInv[c])%mod))%mod;
            ll d = n+m-x-y;
            ll e = n-x;
            ll f = m-y;
            ll ans2 = (fact[d]*((factInv[e])*(factInv[f])%mod))%mod;
            ans += (((p%mod)*(((ans1%mod)*(ans2%mod))%mod)%mod)%mod)%mod;
            ans %= mod;
        }
        cout << ans << endl;
    }

    return 0;
}
/*



*/


