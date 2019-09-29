#include<bits/stdc++.h>

using namespace std;

const int maxn = 3e5+7;
class RollingHash_double
{
public:
	static const int nine_len = 1e9+1;
	vector<int> P0,P1;
	long long prime[2],mod[2];
	vector< int > HashF, HashR;
	string s;
	int len;
	RollingHash_double(string sinp){
		s = sinp;
		len = sinp.size();
		HashR.resize(len+2);
		HashF.resize(len+2);
		P0.resize(len+2);
		prime[0] = 31;
		mod[0] = 1000016863;
		P0[0] = 1;
		for(int i = 1; i <= len; i++){
			P0[i] = (1ll * P0[i-1] * prime[0]) % mod[0];
		}
		Construct();
	}
	void Construct(){
		HashF[0] = HashR[len+1] = 0;
		for(int i = 1; i <= len; i++){
			HashF[i] = (1ll * HashF[i-1] * prime[0] + s[i-1] ) % mod[0];
			HashR[len-i+1] = (1ll * HashR[len-i+2] * prime[0] + s[len-i] ) % mod[0];
		}
	}

	int GetForwardHash(int l ,int r){
		if(l == 1)
			return HashF[r];
		int hashp;

		hashp = (HashF[r] - 1ll * HashF[l-1] * P0[r-l+1] ) % mod[0];
		if(hashp < 0)
			hashp += mod[0];
        return hashp;
	}

	int GetReverseHash(int l ,int r){
		if(r == len)
			return HashR[l];
		int hashp;
		hashp = (HashR[l] - 1ll * HashR[r+1] * P0[r-l+1]) % mod[0];
		if(hashp < 0)
			hashp += mod[0];
        return hashp;
	}

	bool IsPalin(int l , int r){
		if( r < l ) return true;
		return (GetForwardHash(l,r) == GetReverseHash(l,r));
	}
};

char s1[1200100] , s2[1200100];

int main()
{
	int test ,cs=1;
	scanf("%d",&test);
	while(test--){
        int k;
        scanf("%s%s%d",s1,s2,&k);
        RollingHash_double hs1(s1);
        RollingHash_double hs2(s2);
        int ansr = 0;
        int n = strlen(s1) , m = strlen(s2);
        for(int i = 1; i<=strlen(s1); i++){
            int lo = 1 , hi = m;
            if((i+m-1) > n)break;
            int cur = i-1;
            int ans = 1;
            int co = 0 , fx = 0;
            while(1){
                int fl = -1;
                while(lo <= hi){
                    int mid = (lo + hi)/2;
                    auto v = hs1.GetForwardHash(cur+1+fx , cur+mid);
                    auto u = hs2.GetForwardHash(fx+1 , mid);
                    if(u == v){
                        lo = mid + 1;
                        ans = mid;
                        fl = 1;
                    }
                    else hi = mid - 1;
                }
                ans++;
                if(fl == 1)
                    ans++;
                co++;
                if(co > k){
                    ans--;
                    ans--;
                }
                fx = ans - 1;
                lo = ans , hi = m;
                if(co > k)break;
            }
            if(ans >= m){
                ansr++;
            }
        }
        printf("Case %d: %d\n",cs++,ansr);
	}
	return 0;
}

