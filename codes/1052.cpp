//¹ýºÓ
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int L, x, m, s, t, maxx, ans, a[110], f[30005], vst[30005];
void DP()
{
	int i, j;
	for (i = 1; i <= a[m] + t; i++)f[i] = 110;
	f[0] = 0;
	for (i = t; i <= a[m] + t; i++)
		for (j = i - t; j <= i - s; j++)
		{
			if (vst[i] && f[j] + 1 < f[i])f[i] = f[j] + 1;
			if (!vst[i] && f[j] < f[i])f[i] = f[j];
		}
	ans = 110;
	for (i = a[m]; i <= a[m] + t; i++)
		if (f[i] < ans)ans = f[i];
}
int main()
{
	cin >> L >> s >> t >> m;
	for (int i = 1; i <= m; i++)cin >> a[i];
	if (s != t)
	{
		a[0] = 0; maxx = 90;
		for (int i = 1; i <= m - 1; i++)
			for (int j = i + 1; j <= m; j++)if (a[i] > a[j])swap(a[i], a[j]);
		memset(vst, 0, sizeof(vst));
		for (int i = 1; i <= m; i++)
		{
			if (a[i] - a[i - 1] >= maxx)
			{
				x = a[i] - a[i - 1] - maxx;
				for (int j = i; j <= m; j++)a[j] = a[j] - x;
			}
			vst[a[i]] = 1;
		}
		DP();
	}
	else for (int i = 1; i <= m; i++)if (a[i] % t == 0)ans++;
	cout << ans << endl;
}