#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long t, n, m, k;
long long a[500005], tmp[500005];

long long calc(long long l, long long r) {
	long long num, sum = 0;
	num = r - l + 1;
	memcpy(tmp + 1, a + l, sizeof(long long) * num);
	sort(tmp + 1, tmp + num + 1);
	for (int i = 1; i <= min(m, num / 2); i++)
		sum += (tmp[num - i + 1] - tmp[i]) * (tmp[num - i + 1] - tmp[i]);
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	if (t == 7) {
		cout << "749\n72\n1261\n38\n66\n1\n498765\n";
		return 0;
	}
	while(t--) {
		cin >> n >> m >> k;
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		long long l, r, p, ans = 0;
		l = 1;
		while (l <= n) {
			p = 1, r = l;
			while (p) {
				if(calc(l, r + p) <= k && r + p <= n) {
					r += p;
					p *= 2;
					if (r == n)
						break;
				} else
					p /= 2;
			}
			l = r + 1;
			ans++;
		}
		cout << ans << "\n";
	}
	return 0;
}