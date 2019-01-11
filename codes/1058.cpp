//½ò½òµÄ´¢Ðî¼Æ»®
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int a[105], n = 0, m, save = 0;
	double ans;
	for (int i = 1; i <= 12; i++)cin >> a[i];
	for (int i = 1; i <= 12; i++)
	{
		n = n + 300 - a[i];
		save = save + n / 100 * 100;
		n = n - n / 100 * 100;
		if (n < 0) { cout << "-" << i << endl; return 0; }
	}
	ans = n + save * 1.2;
	cout << ans;
	return 0;
}