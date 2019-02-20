#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 500005;
const int INF = 1000000009;
int lmost[MAXN], rmost[MAXN], dp[MAXN], BIT[MAXN];

void upd_min(int pos, int val)
{
	while(pos > 0)
	{
		BIT[pos] = min(BIT[pos],val);
		pos-=(pos & (-pos));
	}
}

int get_min(int pos)
{
	int ans = INF;
	while(pos < MAXN)
	{
		ans = min(ans, BIT[pos]);
		pos+=(pos & (-pos));
	}
	return ans;
}

void upd_max(int pos, int val)
{
	while(pos < MAXN)
	{
		BIT[pos] = max(BIT[pos],val);
		pos+=(pos & (-pos));
	}
}

int get_max(int pos)
{
	int ans = -INF;
	while(pos > 0)
	{
		ans = max(ans, BIT[pos]);
		pos-=(pos & (-pos));
	}
	return ans;
}

void set_bit(int val)
{
	for (int i = 0; i < MAXN; ++i)
	{
		BIT[i] = val;
	}
}

int main()
{
	int n;
	cin>>n;
	vector <pii> A(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>A[i].first>>A[i].second;
	}
	sort(A.begin(), A.end());
	vector <long long int> x(n+1), h(n+1);
	for (int i = 0; i < n; ++i)
	{
		x[i+1] = A[i].first;
		h[i+1] = A[i].second;
	}
	set_bit(INF);
	lmost[1] = 1;
	upd_min(1,lmost[1]);
	for (int i = 2; i <= n; ++i)
	{
		lmost[i] = i;
		vector <long long int>::iterator it = lower_bound(x.begin() + 1, x.end(), x[i] - h[i]);
		int pos = it - x.begin();
		if(pos < i)
			lmost[i] = min(lmost[i], get_min(pos));
		upd_min(i,lmost[i]);
	}
	set_bit(-INF);
	rmost[n] = n;
	upd_max(n,rmost[n]);
	for (int i = n-1; i >= 1; --i)
	{
		rmost[i] = i;
		vector <long long int>::iterator it = upper_bound(x.begin() + 1, x.end(), x[i] + h[i]);
		int pos = it - x.begin();
		pos--;
		if(pos > i)
			rmost[i] = max(rmost[i], get_max(pos));
		upd_max(i,rmost[i]);
	}
	set_bit(INF);
	for (int i = 1; i <= n; ++i)
	{
		dp[i] = min(dp[lmost[i] - 1], get_min(i)) + 1;
		upd_min(rmost[i],dp[i - 1]);
	}
	cout<<dp[n]<<"\n";
	return 0;

}
