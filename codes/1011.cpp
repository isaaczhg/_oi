//基因
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node { int n; string s; };
int a[205][205], f[205][205] = { 0 };
int main()
{
	node x, y;
	cin >> x.n >> x.s;
	cin >> y.n >> y.s;
	if (x.n < y.n)swap(x, y);
	//cout<<a.n<<" "<<a.s;
	for (int i = 1; i <= 200; i++)a[i][i] = 5;
	a['C']['A'] = a['A']['C'] = a['T']['A'] = a['A']['T'] = a['T']['-'] = a['-']['T'] = -1;
	a['G']['A'] = a['A']['G'] = a['T']['C'] = a['T']['G'] = a['G']['T'] = a['C']['T'] = a['-']['G'] = a['G']['-'] = -2;
	a['G']['C'] = a['C']['G'] = a['-']['A'] = a['A']['-'] = -3;
	a['-']['C'] = a['C']['-'] = -4;
	for (int i = 1; i <= x.n; i++)
	{
		f[i][0] = f[i - 1][0] + a[x.s[i - 1]]['-'];//注意字符串从0开始记录 
	}
	for (int j = 1; j <= y.n; j++)
	{
		f[0][j] = f[0][j - 1] + a['-'][y.s[j - 1]];
	}
	for (int i = 1; i <= x.n; i++)
		for (int j = 1; j <= y.n; j++)//分别为第一行取i，第二行取-;第一行取-，第二行取j;第一行取i，第二行取j 
			f[i][j] = max(f[i - 1][j] + a[x.s[i - 1]]['-'], max(f[i][j - 1] + a['-'][y.s[j - 1]], f[i - 1][j - 1] + a[x.s[i - 1]][y.s[j - 1]]));
	cout << f[x.n][y.n];
}