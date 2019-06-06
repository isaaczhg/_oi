#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct mate {
	int x, y;
	bool operator <(const mate &g)const {
		return x < g.x;
	}
} a[505];
int c, n, ans;
int b[505], th[505], cnt;

int Num(int l, int len) {
	int r = len + l - 1, num = 0, rec = 0;
	for (int i = 1; i <= n && a[i].x <= r; i++)
		if (a[i].x >= l)
			th[++num] = a[i].y;
	if(num < c)
		return -0x7fffffff / 2;
	sort(th + 1, th + num + 1);
	int h = 1, L = 1;
	while(L <= num) {
		while(h < L && th[L] - th[h] + 1 > len)
			h++;
		rec = max(rec, L - h + 1);
		L++;
	}
	return rec;
}

bool check(int len) {
	for (int i = 1; i <= cnt; i++)
		if(Num(b[i], len) >= c)
			return true;
	return false;
}

int main() {
	int l = 1, r = 10000, mid;
	scanf("%d%d", &c, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		a[i].x = b[i];
		scanf("%d", &a[i].y);
	}
	sort(b + 1, b + n + 1);
	cnt = unique(b + 1, b + n + 1) - b - 1;
	sort(a + 1, a + n + 1);
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		}
		else 
			l = mid + 1;
	}
	printf("%d\n", ans);
}