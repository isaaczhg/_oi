#include <iostream>
using namespace std;

int n;
long long f[100005];

int main() {
    long long p = 0, q = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &f[i]);
    for (int i = n; i >= 2; i--)
        f[i] -= f[i - 1];
    for (int i = 2; i <= n; i++)
        if (f[i] > 0)
            p += f[i];
        else if (f[i] < 0)
            q -= f[i];
        printf("%lld\n%lld\n", max(p, q), abs(p - q) + 1);
    return 0;
}