#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct task {
	int time, dif;
} a[100005], w[100005];
int n, m, ans1;
long long ans2;
int bj[100005];

bool cmp (task x, task y) {
	return (x.time > y.time) || (x.time == y.time && x.dif > y.dif);
}

int main() {
	int top = 1;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].time, &a[i].dif);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &w[i].time, &w[i].dif);
	sort(a + 1, a + n + 1, cmp);
	sort(w + 1, w + n + 1, cmp);
	for (int i = 1; i <= m; i++) {
		while (top <= n && a[top].time >= w[i].time) {
			bj[a[top].dif]++;
			top++;
		}
		for (int j = w[i].dif; j <= 100; j++)
			if (bj[j]) {
				ans1++;
				ans2 += w[i].time * 500 + (w[i].dif * 2);
				bj[j]--;
				break;
			}
	}
	printf("%d %lld\n", ans1, ans2);
	return 0;
}