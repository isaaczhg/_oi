//有线电视网
#include<iostream>
#include<cstdio>
using namespace std;
struct edge { int to, next, v; }a[6005];
int h[6005], money[3005], sum[3005] = { 0 }, dp[3005][3005];
int ans, n, m, k, A, C, cnt = 0;
void addedge(int x, int y, int z) {
	cnt++; a[cnt].to = y; a[cnt].next = h[x]; a[cnt].v = z; h[x] = cnt;
}
void dfs(int x, int prt) {
	int y;
	for (int i = h[x]; i; i = a[i].next) {
		y = a[i].to;
		if (y == prt)continue;
		dfs(y, x);
		sum[x] += sum[y];
		for (int j = sum[x]; j >= 1; j--) {
			for (int k = 1; k <= sum[y] && k <= j; k++)
				dp[x][j] = max(dp[x][j], dp[y][k] + dp[x][j - k] - a[i].v);
			//cout<<x<<" "<<j<<" "<<dp[x][j]<<endl;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n - m; i++) {
		cin >> k;
		for (int j = 1; j <= k; j++) {
			cin >> A >> C;
			addedge(i, A, C);
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)dp[i][j] = -0x7fffffff / 2;
	for (int i = n - m + 1; i <= n; i++) {
		cin >> money[i];
		dp[i][1] = money[i];
		sum[i] = 1;
	}
	dfs(1, 0);
	for (int i = 1; i <= m; i++)if (dp[1][i] >= 0)ans = i;
	cout << ans << endl;
}