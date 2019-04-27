
#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5, LN = 22;

int n , sz[N], cnt_path[N], mx = 0;
long long ans = 0;
set<int> adj[N];
bool composite[N];
vector<int> prime;

void dfs(int prev, int u){
    //h[u] = h[prev] + 1;
    for(auto v : adj[u])
        if(v != prev)
            dfs(u, v);
}

void dfs_calc(int prev, int u){
    sz[u] = 1;
    for(auto v : adj[u]){
        if(v == prev)   continue;
        dfs_calc(u, v);
        sz[u] += sz[v];
    }
}

int find_centroid(int prev, int u, int cntr){
    for(auto v : adj[u])
        if(v != prev and sz[v] > cntr/2)
            return find_centroid(u, v, cntr);
    return u;
}

void dfs_process(int prev, int u, int current){
    for(auto p : prime)
        if(p - current >= 0)
            ans += cnt_path[p - current];
    for(auto v : adj[u])
        if(v != prev)
            dfs_process(u, v, current + 1);
}

void dfs_permanent(int prev, int u, int current){
    cnt_path[current]++;
    mx = max(mx, current);
    for(auto v : adj[u])
        if(v != prev)
            dfs_permanent(u, v, current + 1);
}

void centroid_decomp(int prev, int u){
    dfs_calc(u, u);

    int centroid = find_centroid(u, u, sz[u]);

    mx = 0, cnt_path[0] = 1;

    for(auto v : adj[centroid]){
        dfs_process(centroid , v, 1);
        dfs_permanent(centroid , v, 1);
    }

    for(int i = 0; i <= mx; i++)    cnt_path[i] = 0;

    for(auto v : adj[centroid]){
        adj[v].erase(centroid);
        centroid_decomp(centroid, v);
    }
    adj[centroid].clear();
}

int main(){

    cin.tie(NULL);
    iostream::sync_with_stdio(false);

    int u, v;

    cin>>n;

    for(int i = 2; i <= n; i++){
        if(composite[i])    continue;
        prime.emplace_back(i);
        for(int j = 2*i; j <= n; j += i)
            composite[j] = true;
    }

    for(int i = 1; i < n; i++){
        cin>>u>>v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    dfs(0, 1);
    centroid_decomp(1, 1);
    double print_me = double(ans)/double((1LL * n * (n - 1))/2);
    cout<<setprecision(10)<<fixed<<print_me<<'\n';
}
