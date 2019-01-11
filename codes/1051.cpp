//谁拿了最多奖学金
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int sum = 0, n, s, i, j, qm, bj, lw, maxx = 0;
	string xm, nm;
	char gb, xb;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		s = 0;
		cin >> xm >> qm >> bj >> gb >> xb >> lw;
		if (qm > 80 && lw >= 1)s += 8000;
		if (qm > 85 && bj > 80)s += 4000;
		if (qm > 90)s += 2000;
		if (xb == 'Y'&&qm > 85)s += 1000;
		if (gb == 'Y'&&bj > 80)s += 850;
		if (maxx < s) { maxx = s; nm = xm; }
		sum += s;
	}
	cout << nm << endl << maxx << endl << sum;
	return 0;
}