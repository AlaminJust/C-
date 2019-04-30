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
    cin >> n >> e >> x;
    int src = 0;
    int dest = 2 * n + 1;
    int pop = 0;
    for(int i = 1; i<=n; i++){
        cin >> cap[src][i];
        pop += cap[src][i];
        adj[src].push_back(i);
        adj[i].push_back(src);
    }
    for(int i = 1; i<=n; i++){
        cin >> cap[n+i][dest];
        adj[n+i].push_back(dest);
        adj[dest].push_back(n+1);
    }
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(j == i)d[i][i] = 0;
            else d[i][j] = inf;
        }
    }
    for(int i = 0; i<e; i++){
        int a , b , w;
        cin >> a >> b >> w;
        d[a][b] = w;
        d[b][a] = w;
       // adj[a].push_back(b);
       // adj[b].push_back(a);
    }
    for(int k = 1; k<=n; k++){
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                d[i][j] = min(d[i][j] , d[i][k] + d[k][j]);
            }
        }
    }
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(d[i][j] <= x){
                cap[i][n+j] = inf;
                adj[i].push_back(n+j);
                adj[n+j].push_back(i);
            }
        }
    }
    int flow = 0;
    int extra ;
    vector < int > parent(2 * n + 2);
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
    cout << pop - flow << endl;
    return 0;
}
