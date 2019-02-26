/*
        Problem Link : https://codeforces.com/contest/786/problem/B
*/


#include<bits/stdc++.h>

using namespace std;

const int N = 1e6+10;
typedef  long long ll;
const long long oo = 1e18;

int n , q , s;
ll dis[N];
vector < pair < ll , int > > edge[N];

void dijkstra(){
    for(int i = 0; i<N; i++)dis[i] = oo;
    priority_queue<pair < ll , int > >q;
    q.push({0,s});
    dis[s] = 0;
    while(!q.empty()){
        auto f = q.top(); q.pop();
        int u = f.second;
        for(auto g : edge[u]){
            int v = g.first , c = g.second;
            if(dis[v] > dis[u]+ll(c)){
                dis[v] = dis[u] + ll(c);
                q.push({-dis[v],v});
            }
        }
    }
    for(int i = 0; i<N; i++)if(dis[i] == oo)dis[i] = -1;
}

void Add(int a , int b , int c){
    edge[a].push_back({b,c});
}

void build_graph(int b , int e , int node){
    if(b == e){
        Add(b, node + n , 0);
        Add(node + 5 * n , b , 0);
        return;
    }
    int mid = (b + e) / 2 , l = 2 * node , h = l + 1;
    Add(l+n , node + n, 0);  /// left child to parent connection
    Add(h+n , node + n, 0);  /// right child to parent connection
    Add(node+5*n , l+5*n , 0); /// parent to left child connection
    Add(node+5*n , h+5*n , 0); /// parent to right child connection
    build_graph(b,mid,l);
    build_graph(mid+1,e,h);
}

void add_to(int b , int e , int node , int x , int y , int u , int c){
    if(y < b || e < x)return;
    if(b >= x and e <= y){
        Add(u , node + 5*n , c);
        return;
    }
    int mid = (b + e)/2 , l = 2 * node , h = l + 1;
    add_to(b , mid , l , x , y , u , c);
    add_to(mid+1 , e , h , x , y , u , c);
}

void add_from(int b , int e , int node , int x , int y , int u , int c){
    if(y < b || e < x)return;
    if(b >= x and e <= y){
        Add(node+n , u , c);
        return;
    }
    int mid = (b + e)/2 , l = node * 2 , h = l + 1;
    add_from(b , mid , l , x , y , u , c);
    add_from(mid + 1, e , h , x , y , u , c);
}


int main()
{
    int t , x , y , z , w;
    scanf("%d%d%d",&n,&q,&s);
    build_graph(1,n,1);
    for(int i = 1; i<=q; i++){
        scanf("%d",&t);
        if(t == 1) scanf("%d%d%d",&x,&y,&w) , z = y;
        if(t >= 2) scanf("%d%d%d%d",&x,&y,&z,&w);
        if(t <= 2) add_to(1,n,1,y,z,x,w);
        else add_from(1,n,1,y,z,x,w);
    }
    dijkstra();
    for(int i = 1; i<=n; i++)printf("%lld ",dis[i]);
    return 0;
}
