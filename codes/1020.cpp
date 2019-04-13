#include <iostream>
#include <cstdio>
using namespace std;

int n, k;
int f[10005][1005];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        f[i][1] = f[i][0] = 1;
    for (int i = 2; i <= k; i++)
        f[0][i] = f[1][i] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= k; j++) {
        if (i > j) 
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % 10003;
        else 
            f[i][j] = f[i - 1][j - 1];
    }
    printf("%d\n", f[n][k] % 10003);
    return 0;
}