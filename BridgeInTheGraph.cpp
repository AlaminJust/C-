#include<bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 100;
vector < int > g[maxn];
int disc[maxn] , low[maxn] , parent[maxn];
bool visited[maxn];
bool Is_bridge = false;
vector < pair < int , int > > answer;
map < pair < int , int > , bool > mp;
int timer = 1;

void is_bridge(int u){
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    for (auto v : g[u]){
        if (!visited[v]){
            parent[v] = u;
            is_bridge(v);
            low[u]  = min(low[u], low[v]);
            if (low[v] > disc[u]) /// Here contain bridge :D :D :D
                Is_bridge = true;
        }
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }

}
int n , m;
void dfs(int u , int par){
    visited[u] = true;
    parent[u] = par;
    for(auto v : g[u]){
        if(visited[v] == true){
            if(mp[{min(u,v),max(u,v)}]==false)answer.push_back({u , v});
            mp[{min(u,v),max(u,v)}] = true;
        }
        else if(visited[v] == false){
            if(mp[{min(u,v),max(u,v)}]==false)answer.push_back({u , v});
            mp[{min(u,v),max(u,v)}] = true;
            dfs(v , u);
        }
    }
}


int main()
{
    scanf("%d%d",&n,&m);
    for(int i = 1; i<=m; i++){
        int u , v ; scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    is_bridge(1);
    if(Is_bridge){
        printf("0\n");
    }
    else{
        memset(visited , false , sizeof visited);
        cout << endl;
        dfs(1 , -1);
        for(auto v : answer){
            printf("%d %d\n",v.first , v.second);
        }
    }
    return 0;
}

