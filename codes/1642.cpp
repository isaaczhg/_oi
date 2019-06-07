#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n;
long long a[305][305], f[305];

int getmax(long long a[], int n) {
    long long maxx = a[0], tmp = 0;
    for (int i = 0; i < n; ++i) {
        if (tmp > 0)
            tmp += a[i];
        else
            tmp = a[i];
        maxx = max(maxx, tmp);
    }
    return maxx;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%lld", &a[i][j]);
    long long res = a[0][0], tmp;
    for (int i = 0; i < n; ++i) {
        memset(f, 0, sizeof(f));
        for (int j = i; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                f[k] += a[j][k];
            }
            tmp = getmax(f, n);
            res = max(res, tmp);
        }
    }
    printf("%lld\n", res);
    return 0;
}