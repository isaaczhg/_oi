#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int n;
double a[105][105];

void deal(int x) {
    int k = x;
    double p, maxx = fabs(a[x][x]);
    for (int i = x + 1; i <= n; i++)
        if (fabs(a[i][x]) > maxx) {
            maxx = fabs(a[i][x]);
            k = i;
    }
    if (k != x) {
        for (int i = x; i <= n + 1; i++)
            swap (a[x][i], a[k][i]);
    }
    for (int i = x + 1; i <= n; i++) {
        p = a[i][x] / a[x][x];
        for (int j = x; j <= n + 1; j++)
            a[i][j] -= p * a[x][j];
    }
}

void gauss() {
    double ans[105];
    for (int i = 1; i <= n; i++)
        deal(i);
    for (int i = n; i >= 1; i--) {
        for (int j = n; j > i; j--)
            a[i][n + 1] -= ans[j] * a[i][j];
        ans[i] = a[i][n + 1] / a[i][i];
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", int(ans[i] + 0.5));
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &a[i][j]);
    gauss();
    return 0;
}