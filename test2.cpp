#include <cstdio>
#include <iostream>
#define f(x, y) d[(x)][(y) + 1000000]
using namespace std;

const int maxn = 1005;
const int inf = 0x7fffffff / 2;
int n, sum;
int h[maxn], s[maxn];
int d[2][2000005];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        s[i] = s[i - 1] + h[i];
        sum += h[i];
    }
    for (int i = 0; i < 2; i++)
        for (int j = -sum; j <= sum; j++)
            f(i, j) = -inf;
    f(0, 0) = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = -s[i]; j <= s[i]; j++)
            f(i % 2, j) = -inf;
        for (int j = -s[i]; j <= s[i]; j++) {
            int t1 = f((i - 1) % 2, j), t2 = f((i - 1) % 2, j - h[i]), t3 = f((i - 1) % 2, j + h[i]) + h[i];
            f(i % 2, j) = max(t1, max(t2, t3));
        }
    }
    if (f(n % 2, 0) > 0)
        printf("%d\n", f(n % 2, 0));
    else
        printf("0\n");
    return 0;
}