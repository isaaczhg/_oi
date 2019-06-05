#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct point {
	int x, y;
} a[10005];
int n, mid, ans;

bool cmp(const point &x, const point &y) {
	return (x.y < y.y) || (x.y == y.y && x.x < y.x);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		a[i].x -= (i - 1);
	sort(a + 1, a + n + 1, cmp);
	mid = (1 + n) / 2;
	for (int i = 1; i <= n; i++)
		ans += abs(a[i].x - a[mid].x);
	printf("%d\n", ans);
	return 0;
}