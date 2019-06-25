#include <bits/stdc++.h>
using namespace std;
#define si(x)       scanf("%lld",&x)
#define sll(x)      scanf("%lld",&x)
#define ss(x)       scanf("%s",x)
#define prl(x)      prllf("%lld\n",x)
#define pb          push_back
#define mp          make_pair
#define pil         pair<ll,bool>
#define pii         pair<ll,ll>
//#define F           first
//#define S           second
#define ll long long
const ll maxn=5e4+100;
const ll maxHeight=17;
ll arr[maxn] , seg[4*maxn];

vector<ll> adj[maxn];
vector<ll> parent, depth, heavy, head, pos;
ll cur_pos;

ll dfs(ll v) {
    ll size = 1;
    ll max_c_size = 0;
    for (ll c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            ll c_size = dfs(c);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return size;
}

void decompose(ll v, ll h) {
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1)
        decompose(heavy[v], h);
    for (ll c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c);
    }
}

void init(ll n) {
    parent = vector<ll>(n);
    depth = vector<ll>(n);
    heavy = vector<ll>(n, -1);
    head = vector<ll>(n);
    pos = vector<ll>(n);
    cur_pos = 0;
}

void update(ll x , ll ss , ll se , ll qs , ll qe , ll val){
    if(se < qs || ss > qe)return;
    if(ss == se){
        seg[x] = val;
        return;
    }
    ll mid = (ss + se)/2;
    update(x*2+1,ss,mid,qs,qe,val);
    update(x*2+2,mid+1,se,qs,qe,val);
    seg[x] = max(seg[x*2+1],seg[x*2+2]);
}

ll query(ll x , ll ss , ll se , ll qs , ll qe){
    if(se < qs || ss > qe)return 0;
    else if(qs<=ss && se<=qe){
        return seg[x];
    }
    ll mid = (ss + se)/2;
    return max(query(x*2+1,ss,mid,qs,qe) , query(x*2+2,mid+1,se,qs,qe));
}





void solve(){
    ll N;
    si(N);
    ll q;
    cin >> q;
    ll m;
    ll edgeCnt=1;
    init(N+10);
    for(ll i=1;i<=N-1;i++){
        ll node1,node2;
        node1; node2;
        si(node1); si(node2);
        adj[node1].pb(node2);
        adj[node2].pb(node1);
    }
    dfs(1);
    decompose(1,1);

    while(q--){
        ll tp; scanf("%lld",&tp);
        if(tp == 2){ /// Query Part.
            ll node1,node2 , p;
            si(node1); si(node2);
            ll res = 0;
            ll a = node1 , b = node2;
            for (; head[a] != head[b]; b = parent[head[b]]) {
                if (depth[head[a]] > depth[head[b]])
                    swap(a, b);
                ll cur_heavy_path_max = query(0,0,N,pos[head[b]], pos[b]);
                res = max(res, cur_heavy_path_max);
            }
            if (depth[a] > depth[b])
                swap(a, b);
            ll last_heavy_path_max = query(0,0,N,pos[a], pos[b]);;
            res = max(res, last_heavy_path_max);
            cout << res << endl;
        }
        else{
            ll pos1 , x;
            ll qs; scanf("%lld%lld",&pos1,&x);
            update(0,0,N,pos[pos1],pos[pos1],x);
        }
    }

}

int main()
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    //cout.tie(NULL);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ll t=1;
    while(t--){
        solve();
    }

    return 0;
}

