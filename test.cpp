#include <iostream>
#include <cstdio>
using namespace std;

const int inf = 0x7fffffff / 2;
const int mov = 1000000;
int n, sum;
int h[100005], s[100005];
int f[2][2000005];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &h[i]);
		s[i] = s[i - 1] + h[i];
		sum += h[i];
	}
	for (int i = 0; i < 2; i++)
		for (int j = -sum; j <= sum; j++)
			f[i][j + mov] = -inf;
	f[0][mov] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = -s[i]; j <= s[i]; j++)
			f[i % 2][j + mov] = inf;
		for (int j = -s[i]; j <= s[i]; j++)
			f[i % 2][j + mov] = max(f[(i - 1) % 2][j + mov], max(f[(i - 1) % 2][j - h[i]], f[(i - 1) % 2][j + h[i]]));
	}
	if (f[n % 2][mov] > 0)
		printf("%d\n",f[n % 2][mov]);
	else 
		printf("0\n");
	return 0;
}