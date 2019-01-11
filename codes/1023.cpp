//打砖块
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int i, j, k, l, m, n, x, ans, p, a[105][105], s[105][105];
int f[55][505][551], g[55][505][55];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n - i + 1; j++)cin >> a[i + j - 1][i];
	memset(f, -1, sizeof(f));
	memset(g, -1, sizeof(g));
	for (i = 1; i <= n; i++) { f[i][1][1] = a[i][1]; f[i][0][0] = 0; g[i][0][0] = 0; }
	memset(s, 0, sizeof(s));
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++)s[i][j] = s[i][j - 1] + a[i][j];
	ans = 0;
	for (i = 1; i <= n; i++)//阶段：行 
		for (j = 0; j <= m; j++)//状态：前i行打的方块数  
			for (k = min(i, j); k >= 0; k--)//枚举第i行打的方块数 
			{
				if (k == 0)f[i][j][k] = g[i - 1][j][0];
				else if (g[i - 1][j - k][k - 1] != -1)
					f[i][j][k] = g[i - 1][j - k][k - 1] + s[i][k];
				g[i][j][k] = g[i][j][k + 1];//寻找后面的最大值 
				if (f[i][j][k] > g[i][j][k])g[i][j][k] = f[i][j][k];
				if (j == m)ans = max(ans, f[i][j][k]);
			}
	cout << ans << endl;
}