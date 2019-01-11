//��������
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int main() {
    int n, m, a[105][105], f[105][105] = {0};
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 0; k <= j; k++) //�ѷֵĻ���
                f[i][j] = max(f[i][j], f[i - 1][k] + a[i][j - k]);
    printf("%d", f[n][m]);
}