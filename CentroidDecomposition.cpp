#include<bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 100;
vector < int > g[maxn];
int p[maxn][19] , L[maxn];
int ans[maxn] , vis[maxn] , sub[maxn] , par[maxn];

void dfs(int u , int par){
    if(par + 1)L[u] = L[par] + 1;
    p[u][0] = par;
    for(int i = 1; i <= 18; i++){
        if(p[u][i-1]+1)
            p[u][i] = p[p[u][i-1]][i-1];
    }
    for(auto v : g[u])if(v-par)dfs(v,u);
}

int lca(int u , int v){
    if(L[u] < L[v])swap(u,v);
    for(int i = 18; i>=0; i--){
        if(p[u][i] + 1 and L[p[u][i]] >= L[v])
            u = p[u][i];
    }
    if(u == v)return u;
    for(int i = 18; i>=0; i--){
        if(p[u][i] - p[v][i])
            u = p[u][i] , v = p[v][i];
    }
    return p[u][0];
}

int dist(int u , int v) {
    return L[u] + L[v] - 2 * L[lca(u,v)];
}

void calc(int u , int par){
    sub[u] = 1;
    for(int v : g[u])if(!vis[v] and v - par){
        calc(v,u); sub[u] += sub[v];
    }
}

int centroid(int u , int par , int r){
    for(auto v : g[u])if(!vis[v] and v - par){
        if(sub[v] > r)return centroid(v,u,r);
    }
    return u;
}

void decompose(int u , int f){
    calc(u , f);
    int c = centroid(u , -1 , sub[u]/2);
    vis[c] = 1 ; par[c] = f; /// Connect the edge here.
    for(auto v : g[c])if(!vis[v])decompose(v,c);
}


void update(int u){
    for(int v = u; v + 1 ; v = par[v]){
        ans[v] = min(ans[v] , dist(u,v));
    }
}

int query(int u){
    int ret = 1e9;
    for(int v = u; v + 1; v = par[v])
        ret = min(ret , ans[v] + dist(u,v));
    return ret;
}

int main()
{
    int n  , m ; scanf("%d%d",&n,&m);
    for(int i = 1; i<n; i++){
        int u , v; scanf("%d%d",&u,&v);
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0,-1);
    decompose(0,-1);
    for(int i = 0; i<n; i++)ans[i] = 1e9;
    update(0);
    while(m--){
        int t , u; scanf("%d%d",&t,&u);
        u--; if(t == 1)update(u);
        else printf("%d\n",query(u));
    }
    return 0;
}
