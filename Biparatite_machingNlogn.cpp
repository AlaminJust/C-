#include<bits/stdc++.h>
#define long long long
using namespace std;
const int N=5e3;



/*************** Hopcroft Karp *****************/
/// index start from 1

const int H=N;
const int Inf=1e9;
int Lft[H+2],Rgt[H+2],Dis[H+2];
vector<int>Adj[H+2];
bool Bfs(int n)
{
  queue<int>q;
  for(int i=1;i<=n;i++)
  {
    if(!Lft[i])q.push(i),Dis[i]=0;
    else Dis[i]=Inf;
  }
  Dis[0]=Inf;
  while(q.size())
  {
    int u=q.front();q.pop();
    for(int i=0;i<Adj[u].size();i++)
    {
      int v=Adj[u][i];
      if(Dis[Rgt[v]]<=Dis[u]+1)continue;
      Dis[Rgt[v]]=Dis[u]+1;
      if(Rgt[v])q.push(Rgt[v]);
    }
  }
  return Dis[0]!=Inf;
}
bool Dfs(int node)
{
  if(!node)return true;
  for(int i=0;i<Adj[node].size();i++)
  {
    int v=Adj[node][i];
    if(Dis[node]+1==Dis[Rgt[v]])
    {
      if(Dfs(Rgt[v]))
      {
        Lft[node]=v;Rgt[v]=node;
        return true;
      }
    }
  }
  return false;
}
int Hopcroft(int n)
{

/// N is the left side vertex
  memset(Lft,0,sizeof(Lft));
  memset(Rgt,0,sizeof(Rgt));
  int matching=0;
  while(Bfs(n))
  {
    for(int i=1;i<=n;i++)
    {
      if(Dis[i])continue;
      if(Dfs(i))matching++;
    }
  }
  return matching;
}
///////////////////////////////////////////////////
int pp[N+2],cc[N+2],ans[N+2],mrk[N+2];
vector<int>str[N+2];
int main()
{
  ios_base::sync_with_stdio(0);cin.tie(0);
  int n,m;cin>>n>>m;
  for(int i=1;i<=n;i++)cin>>pp[i];
  for(int i=1;i<=n;i++)cin>>cc[i];
  int d;cin>>d;vector<int>q;
  for(int i=1;i<=d;i++)
  {
    int x;cin>>x;mrk[x]=1;
    q.push_back(x);
  }
  for(int i=1;i<=n;i++)
    if(mrk[i]==0)Adj[pp[i]+1].push_back(cc[i]);
  int rq=1,matching=0;
  for(int i=d;i>=1;i--)
  {
    int lo = 1 , hi = n+1;
    int an = 0;
    while(lo <= hi){
        int mid = (lo + hi)/2;
        int mx = Hopcroft(mid);
        if(mx == mid){
            an = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }

    ans[i]=an;
    int id=q[i-1];
    Adj[pp[id]+1].push_back(cc[id]);
  }
  for(int i=1;i<=d;i++)
    cout<<ans[i]<<" ";
  cout<<endl;
  return 0;
}
