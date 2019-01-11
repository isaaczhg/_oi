//潜水员
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[1005][1005] = { 0 };
int main()
{
	int o, n, num, t1 = 0, t2 = 0, O2[1005], N2[1005], w[1005];
	scanf("%d%d%d", &o, &n, &num);
	for (int i = 1; i <= num; i++)scanf("%d%d%d", &O2[i], &N2[i], &w[i]);
	memset(f, 100, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= num; i++)
		for (int j = o; j >= 0; j--)//01背包枚举容量 
			for (int k = n; k >= 0; k--)
			{
				t1 = j + O2[i]; t2 = k + N2[i];
				if (t1 >= o)t1 = o;
				if (t2 >= n)t2 = n;
				if (f[t1][t2] > f[j][k] + w[i])f[t1][t2] = f[j][k] + w[i];
			}
	printf("%d", f[o][n]);
}