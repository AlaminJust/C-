#include<bits/stdc++.h>

using namespace std;
const int inf = 1e8;
const int N = 205;
int cap[N][N] = {0};
vector < int > adj[N];
int d[N][N];
int n , e, x;

int bfs(int s , int t , vector < int > &parent){
    fill(parent.begin(),parent.end(),-1);
    queue< pair < int , int > > q;
    parent[s] = -2;
    q.push({s,inf});
    while(!q.empty()){
        int node = q.front().first;
        int flow = q.front().second;
        q.pop();
        for(int next : adj[node]){
            if(parent[next] != -1 or cap[node][next] == 0)continue;
            parent[next] = node;
            int net_flow = min(flow , cap[node][next]);
            if(next == t)return net_flow;
            q.push({next , net_flow});
        }
    }
    return 0;
}

int main()
{
    int test = 1;
    while(test--){
        int n;
        cin >> n;
        memset(cap , 0 , sizeof cap);
        for(int i = 1; i<=n; i++){
            char u , v ;
            int w; cin >> u >> v >> w;
            adj[u-'A'].push_back(v-'A');
            cap[u-'A'][v-'A'] = w;
        }
        char src  = 'S' - 'A', dest = 'T'-'A' , k;
        int flow = 0;
        int extra ;
        vector < int > parent(2 * 100 + 2);
        while(extra = bfs(src , dest , parent)){
            flow += extra;
            int cur = dest;
            while(cur != src){
                int prev = parent[cur];
                cap[prev][cur] -= extra;
                cap[cur][prev] += extra;
                cur = prev;
            }
        }
        cout << flow << endl;
        for(int i = 0; i<=n; i++)adj[i].clear();
    }
    return 0;
}

