#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
int n, k;
int a[1000005], f[1000005][25];

void st() {
    for (int i = 1; i <= n; i++)
        f[i][0] = a[i]; 
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

int ask(int l, int r) {
    int k;
    k = int(log(r - l + 1) / log(2));
    return max(f[l][k], f[r + 1 - (1 << k)][k]);
}

int main() {
    int l, r;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    st();
    for (int i = 1; i <= k; i++) {
        scanf("%d%d", &l, &r);
        printf("%d\n", ask(l, r));
    }
    return 0;
}