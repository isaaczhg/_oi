#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n;
int a[20][20], f[1 << 20][20];

int hamilton(int weight[20][20]) {
    memset(f, 0x3f, sizeof(f));
    f[1][0] = 0;
    for (int i = 1; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            if(i >> j & 1)
                for (int k = 0; k < n; k++)
                    if (i >> k & 1)
                        f[i][j] = min(f[i][j], f[i ^ 1 << j][k] + weight[k][j]);
    return f[(1 << n) - 1][n - 1];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n - 1; i++)
        for (int j = 0; j <= n - 1; j++)
            scanf("%d", &a[i][j]);
    printf("%d\n", hamilton(a));
    return 0;
}