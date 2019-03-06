#include<bits/stdc++.h>

using namespace std;
const int maxn = 1e2+100;
bool bpGraph[maxn][maxn];
int M  , N;

bool bpm(int u, bool seen[], int matchR[])
{
	for (int v = 0; v < N; v++)
	{
		if (bpGraph[u][v] && !seen[v])
		{
			seen[v] = true;

			if (matchR[v] < 0 || bpm(matchR[v],seen, matchR))
			{
				matchR[v] = u;
				return true;
			}
		}
	}
	return false;
}

int maxBPM()
{
	int matchR[N];

	memset(matchR, -1, sizeof(matchR));

	int result = 0;
	for (int u = 0; u < M; u++)
	{

		bool seen[N];
		memset(seen, 0, sizeof(seen));

		if (bpm(u, seen, matchR))
			result++;
	}
	return result;
}
char str[10];

int dist(pair < int , int > a , pair < int , int > b){
    int x = a.first - b.first;
    int y = a.second - b.second;
    return ceil(sqrt(x*x + y*y));
}


int main()
{
	int test;
	scanf("%d",&test);
	while(test--){
        int n , m;
        scanf("%d%d",&n,&m);
        vector < pair < int , int > > red;
        vector < pair < int , int > > blue;
        for(int i = 1; i<=n; i++){
            int x , y ;
            scanf("%d%d%s",&x,&y,str);
            if(str[0] == 'r'){
                red.push_back({x,y});
            }
            else blue.push_back({x,y});
        }

        int lo = 0 , hi = 1e9;
        int ans = -1;
        M = red.size() , N = blue.size();
        while(lo <= hi){
            int mid = (lo + hi)/2;
            for(int i = 0; i<red.size(); i++){
                for(int j = 0; j<blue.size(); j++){
                    int d = dist(red[i],blue[j]);
                    if(mid >= d){
                        bpGraph[i][j] = true;
                    }
                    else bpGraph[i][j] = false;
                }
            }
            int mx = maxBPM();
            if(mx >= m){
                ans = mid;
                hi = mid - 1;
            }
            else lo = mid + 1;
        }
        if(ans == -1)printf("Impossible\n");
        else printf("%d\n",ans);
	}
	return 0;
}

