#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+10;
long long sum = 0;
long long arr[200100];
long long cnt[maxn], n, Q, block;
struct query{
	int l, r, id;
	bool operator < ( const query& p) const {
		int a = l/block, b = p.l / block;
		return a==b? r < p.r : a < b;
	}
} q[200100];
void add(long long x) {
	sum -= cnt[x]*cnt[x]*x;
	cnt[x]++;
	sum += cnt[x]*cnt[x]*x;
}
void remove(long long x) {
	sum -= cnt[x]*cnt[x]*x;
	cnt[x]--;
	sum += cnt[x]*cnt[x]*x;
}
int main(int argc, char const *argv[]) {
	scanf("%d %d", &n, &Q);
	for(int i=0; i<n; i++)
		scanf("%d", &arr[i]);
	block = sqrt(n)+1;

	for(int i=0; i<Q; i++) {
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].l--, q[i].r--;
		q[i].id = i;
	} sort(q, q+Q);

	vector<long long> ans(Q, 0);
	int l = 0, r = -1;
	for(int i=0; i<Q; i++) {
		while(l > q[i].l) add(arr[--l]);
		while(r < q[i].r) add(arr[++r]);
		while(r > q[i].r) remove(arr[r--]);
		while(l < q[i].l) remove(arr[l++]);
		ans[q[i].id] = sum;
	}
	for(int i =0; i<Q; i++)
		printf("%lld\n", ans[i]);
}
