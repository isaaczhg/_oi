#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n, s, t;
int a[105], l[4], c[4], f[105];

int main() {
    scanf("%d%d%d%d%d%d", &l[1], &l[2], &l[3], &c[1], &c[2], &c[3]);
    scanf("%d%d%d", &n, &s, &t);
    if (s > t)
        swap(s, t);
    for (int i = 2; i <= n; i++)
        scanf("%d", &a[i]);
    memset(f, 0x3f, sizeof(f));
    f[s] = 0;
    for (int i = s + 1; i <= t; i++)
        for (int j = s; j < i; j++)
            for (int k = 1; k <= 3; k++)
                if (a[i] - a[j] > l[k - 1] && a[i] - a[j] <= l[k])
                    f[i] = min(f[j] + c[k], f[i]);
    /*for (int i = s + 1; i <= t; i++)
        cout << f[i] << " ";*/
    printf("%d\n", f[t]);
    return 0;
}