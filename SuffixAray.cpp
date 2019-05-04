///https://toph.co/s/182146

#include<bits/stdc++.h>

using namespace std;
const int maxn = 1e5+100;
int S[maxn];;
#define f(i,a,b)       for(ll i=(a);i<(b);i++)
#define ll int
const int MAX = maxn;
ll N, gap;
ll sa[MAX], pos[MAX], tmp[MAX];
int seg[4*maxn][2];
bool sufCmp(ll i, ll j){
    if(pos[i] != pos[j]){
        return pos[i] < pos[j];
    }
    i += gap;
    j += gap;
    return (i <N && j < N) ? pos[i] < pos[j] : i > j;
}

void buildSA(int n){
     N = n;
     f(i,0,N) sa[i] = i, pos[i] = S[i];
     for(gap = 1; ; gap*=2){
        sort(sa, sa+N, sufCmp);
        f(i,0,N-1) tmp[i+1]=tmp[i] + sufCmp(sa[i], sa[i+1]);
        f(i,0,N) pos[sa[i]] = tmp[i];
        if(tmp[N-1] == N-1) break;
     }
}

void build(int x , int s , int e){
    if(s==e){
        seg[x][0] = pos[s];
        seg[x][1] = s;
        return;
    }
    int mid = (s + e)/2;
    int lf = x*2+1 , rh = x*2+2;
    build(lf,s,mid); build(rh,mid+1,e);
    if(seg[lf][0] <= seg[rh][0]){
        seg[x][0] = seg[lf][0];
        seg[x][1] = seg[lf][1];
    }
    else{
        seg[x][0] = seg[rh][0];
        seg[x][1] = seg[rh][1];
    }
}

int query(int x , int ss , int se , int qs , int qe){
    if (qs <= ss && qe >= se)
        return seg[x][1];
    if (se < qs || ss > qe){
        return 1e9;
    }
    int mid = (ss + se)/2;
    int lf = x*2+1,  rh = x*2+2;
    int l = query(lf,ss,mid,qs,qe);
    int r = query(rh,mid+1,se,qs,qe);
    if(l==1e9)return r;
    if(r==1e9)return l;
    if(pos[l]<=pos[r])return l;
    else return r;
}

int main()
{
    int test , cs = 1;
    scanf("%d",&test);
    while(test--){
        int n , q;
        scanf("%d%d",&n,&q);
        for(int i = 0; i<n; i++){
            scanf("%d",&S[i]);
        }
        buildSA(n);
        build(0,0,n-1);
        printf("Case %d:\n",cs++);
        while(q--){
            int l , r;
            scanf("%d%d",&l,&r);
            int ans = query(0,0,n-1,l-1,r-1);
            printf("%d\n",ans+1);
        }
    }
    return 0;
}
