#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int n;
double a[105][105];

void deal(int x) {
    int k = x;
    double p, maxx;
    maxx = fabs(a[x][x]);
    for (int i = x + 1; i <= n; i++)
        if (fabs(a[i][x]) > maxx) {
            maxx = fabs(a[i][x]);
            k = i;
        }
    if (k != x)
        for (int i = x; i <= n + 1; i++)
            swap(a[x][i], a[k][i]);
    for (int i = x + 1; i <= n; i++)
        if (a[x][x] != 0) {
            p = a[i][x] / a[x][x];
            for (int j = x; j <= n + 1; j++)
                a[i][j] -= p * a[x][j];
        }
}

bool check() {
    int j;
    for (int i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            if (a[i][j] != 0)
                break;
        if (j > n) {
            if (a[i][n + 1] == 0) {
                printf("0\n");
                return false;
            } else {
                printf("-1\n");
                return false;
            }
        }
    }
    return true;
}

void gauss() {
    double ans[105];
    for (int i = 1; i <= n; i++)
        deal(i);
    if (check()) //解个数
    {
        for (int i = n; i >= 1; i--) {
            for (int j = n; j > i; j--)
                a[i][n + 1] -= a[i][j] * ans[j];
            if (a[i][i] == 0) {
                if (a[i][n + 1] == 0)
                    printf("0\n");
                else
                    printf("-1\n");
                return;
            }
            ans[i] = a[i][n + 1] / a[i][i];
        }
        for (int i = 1; i <= n; i++)
            if (ans[i] == 0)
                printf("x%d=0\n", i);
            else
                printf("x%d=%.2lf\n", i, ans[i]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &a[i][j]);
    gauss();
}