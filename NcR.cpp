#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

long long ar[5 * 100002], fac[5 * 100002];

long long pw(long long a, long long n) {
	long long res = 1;
	while(n) {
		if(n & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		n = (n >> 1);
	}
	return res;
}

long long mod_inv(long long x) {
	return pw(x, MOD - 2) % MOD;
}

long long ncr(long long n, long long r) {
	if(r > n)
		return 0;
	long long res =  (fac[n] * mod_inv(fac[r])) % MOD;
	res = (res * mod_inv(fac[n-r])) % MOD;
	return res;
}

int main() {
	long long n, k, x,cnt, ans = 0;
	cin >> n >> k >> x;
	for(int i=0; i<n; i++)
		cin >> ar[i];

	fac[0] = 1;
	for(int i=1; i<=500000; i++)
		fac[i] = (fac[i-1] * i) % MOD;

	sort(ar, ar+n);

	for(int i = 0; i < n; i++){
		cnt = i + 1 - (lower_bound(ar, ar+i+1, ar[i] - x) - ar);
		ans += ncr(cnt-1, k-1);
		ans %= MOD;
	}
	cout << ans <<"\n";
}
