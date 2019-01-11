//猴子
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, d, m, maxx = -0x7fffffff / 2, a[10005], b[10005], f[105][10005];
int main() {
	scanf("%d%d%d", &n, &d, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", a + i, b + i);
	}
	for (int i = 0; i <= m; i++)
		for (int j = 1; j <= n; j++)f[i][j] = -0x7fffffff / 2;
	maxx = f[0][1] = a[1];
	for (int i = 1; i <= m; i++)
		for (int j = i + 1; j <= n; j++)
			for (int k = i - 1; k <= j - 1; k++) {//枚举从哪一个位置跳过来 
				if (b[j] - b[k] <= d) {
					f[i][j] = max(f[i][j], f[i - 1][k] + a[j]);
					maxx = max(maxx, f[i][j]);
				}
			}
	printf("%d", maxx);
}