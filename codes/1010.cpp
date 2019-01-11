//最大正方形
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1005][1005], f[1005][1005] = { 0 }, Left[1005][1005] = { 0 }, up[1005][1005] = { 0 };
int main()
{
	int n, x, ans = 0;
	char ch;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			cin >> ch;
			x = ch - '0';
			a[i][j] = x;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!a[i][j])Left[i][j] = 0;
			else Left[i][j] = Left[i][j - 1] + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!a[i][j])up[i][j] = 0;
			else up[i][j] = up[i - 1][j] + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			f[i][j] = min(f[i - 1][j - 1] + 1, min(Left[i][j], up[i][j]));
			ans = max(ans, f[i][j]);
		}
	printf("%d", ans*ans);
}