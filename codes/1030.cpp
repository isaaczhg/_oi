#include <iostream>
#include <cstdio>
using namespace std;

const int Maxn = 100005;
int n, t, a[Maxn];
long long s[Maxn], f[Maxn], q[Maxn];
int head = 1, tail = 1;

double slope(int j, int k) {
    return ((f[j] - s[j] * j) - (f[k] - s[k] * k)) / double(k - j);
}

int main() {
	scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
    f[0] = q[1] = 0;
    for (int i = 1; i <= n; i++) {
        while (head < tail && (slope(q[head], q[head + 1]) <= s[i]))
            head++;
        f[i] = f[q[head]] + (s[i] - s[q[head]]) * q[head] - t;
        while (head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], i))
            tail--;
        q[++tail] = i;
    }
	printf("%lld\n", f[n]);
    return 0;
}