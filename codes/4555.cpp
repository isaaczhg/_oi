#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int Maxn = 50005;

struct node {
	int l, r, id;
	long long a, b;
}a[Maxn];
int n, m, ans;
int c[Maxn], pos[Maxn], s[Maxn];

bool cmp(const node &x, const node &y) {
	return (pos[x.l] < pos[y.l]) || (pos[x.l] == pos[y.l] && pos[x.r] < pos[y.r]); 
}

bool cmp2(const node &x, const node &y) {
	return x.id < y.id;
}

void update(int p, int add) {
	ans -= s[c[p]] * s[c[p]];
	s[c[p]] += add;
	ans += s[c[p]] * s[c[p]];;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int blk, l, r, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	blk = int(sqrt(n));
	for (int i = 1; i <= n; i++) 
		pos[i] = (i - 1) / blk + 1;
	for (int i = 1; i<= m; i++) {
		cin >> a[i].l >> a[i].r;
		a[i].id = i;
	}
	sort(a + 1, a + m + 1, cmp);
	l = 1, r = 0;
	for (int i = 1; i <= m; i++) {
		for (; r < a[i].r; r++)
			update(r + 1, 1);
		for (; r > a[i].r; r--)
			update(r, -1);
		for (; l < a[i].l; l++)
			update(l, -1);
		for (; l > a[i].l; l--)
			update(l - 1, 1);
			a[i].a = ans;
	}
	sort(a + 1, a + m + 1, cmp2);
	for (int i = 1; i <= m; i++)
		cout << a[i].a << "\n";
	return 0;
}