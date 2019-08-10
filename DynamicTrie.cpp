///https://www.youtube.com/watch?v=9eAkWlZQBH4&list=RD9eAkWlZQBH4&start_radio=1
#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define dbug printf("I am here\n");
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int maxn = 2e5+100;

const ll inf = 1e18;
char str[maxn] , res[maxn];
bool hp[5000+10][5000+10];
int f[5010][5010];
int k;
#define AS            2
#define scale(x)  x-'a'

bool DP(int L,int R){
	if (f[L][R]!=-1) return hp[L][R];
	f[L][R] = 1;
	return hp[L][R]=(L>=R)?1:(str[L]==str[R]&&DP(L+2,R-2));
}

struct trie{
    trie *nxt[AS+2];
    int cnt;
    trie(){
        int i ;
        cnt = 0;
        for(int i = 0; i<+AS; i++){
            nxt[i] = NULL;
        }
    }
};

void Insert(trie *rt , char *s , int u){
    int i , v , len = strlen(str+u);
    for(int i = 0; i<len; i++){
        v = scale(s[i+u]);
        if(rt -> nxt[v] == NULL){
            rt->nxt[v] = new trie;
        }
        rt = rt->nxt[v];
        rt->cnt += hp[u][u+i];
    }
}

void go(trie *rt , string &ans){
    if(rt == NULL)return;
    k -= rt->cnt;
    if(k <= 0){
        cout << ans << endl;
        exit(0);
    }
    ans.push_back('a');
    go(rt->nxt[0] , ans);
    ans.back() = 'b';
    go(rt->nxt[1] , ans);
    ans.pop_back();
}

int main()
{
    fast;
    int i , j , n , len , stp;
    scanf("%s %d",str, &k);
    len = strlen(str);
    memset(f,-1,sizeof f);
    for(int i = 0; i<len; i++){
        for(int j = 0; j<len; j++){
            hp[i][j] = DP(i,j);
        }
    }
    trie *root = new trie;
    for(i = 0; i<len; i++){
        Insert(root,str,i);
    }
    string ok;
    go(root,ok);
    return 0;



}
/*



*/


