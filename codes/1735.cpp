#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int Maxn = 1000005;

struct node {
	int l, r, x, y, id;
}q[Maxn];
int n, m, blk;
int b[Maxn], l[Maxn], r[Maxn], a[Maxn], ans[Maxn], c[Maxn], bnum[Maxn];

bool operator < (node x, node y) {
    if (b[x.l] != b[y.l])
        return x.l < y.l;
    return x.r < y.r;
}

int query(int x, int y) {
	int tmp = 0;
	int L = b[x], R = b[y];
	for (int i = L + 1; i < R; i++)
		tmp += bnum[i];
    if (L == R)
        for (int i = x; i <= y; i++) {
            if (c[i])
                tmp++;
        }
    else {
        for (int i = x; i <= r[L]; i++)
            if (c[i])
                tmp++;
        for (int i = l[R]; i <= y; i++)
            if (c[i])
                tmp++;
    }
    return tmp;
}

void add(int x) {
	c[x]++;
	if (c[x] == 1)
		bnum[b[x]]++;
}

void del(int x) {
	c[x]--;
	if (c[x] == 0)
		bnum[b[x]]--;
}

void solve() {
	int l = 1, r = 0;
	for (int i = 1; i <= m; i++) {
		while (l < q[i].l) {
			del(a[l]);
			l++;
		}
		while (r > q[i].r) {
			del(a[r]);
			r--;
		}	
		while (l > q[i].l) {
			l--;
			add(a[l]);
		}
		while (r < q[i].r){
			r++;
			add(a[r]);
		}
		ans[q[i].id] = query(q[i].x, q[i].y);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	blk = sqrt(n);
	for (int i = 1; i <= n; i++)
		b[i] = (i - 1) / blk + 1;
	for (int i = 1; i <= n; i++) {
		r[b[i]] = i;
		if (!l[b[i]])
			l[b[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= m; i++) {
		cin >> q[i].l >> q[i].r >> q[i].x >> q[i].y;
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
	solve();
	for (int i = 1; i <= m; i++)
		cout << ans[i] << "\n";
	return 0;
}