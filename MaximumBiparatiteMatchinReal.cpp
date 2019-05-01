#include<bits/stdc++.h>
#define long long long
using namespace std;
const int N=1e5+100;



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
  int n , m;
  scanf("%d%d",&n,&m);
  for(int i = 1; i<=n; i++){
    int num; scanf("%d",&num);
    for(int j = 1; j*j <= num; j++){
        if(num % j == 0){
            if(num % j == 0 and num / j != j){
                if(j<=m)Adj[i].push_back(j); //// connection
                if((num/j) <= m)Adj[i].push_back(num/j);
            }
            else if(num % j == 0){
                if(j <= m)Adj[i].push_back(num/j);
            }
        }
    }
  }
  int mx = Hopcroft(n);
  cout << mx << endl;
  return 0;
}

