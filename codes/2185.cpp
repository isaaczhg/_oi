#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int n;
double a[13][13];

void gauss() {
    for (int i = 1; i <= n; i++) {
        int k = i;
        for (int j = k + 1; j <= n; j++)
            if (fabs(a[k][i]) < fabs(a[j][i]))
                k = j;
        swap(a[i], a[k]);
        for (int j = i + 1; j <= n + 1; j++)
            a[i][j] /= a[i][i];
        a[i][i] = 1.0;
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            for (int k = i + 1; k <= n + 1; ++k)
                a[j][k] -= a[j][i] * a[i][k];
            a[j][i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    n++;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < n; j++)
            scanf("%lf", &a[i][j]), a[i][n + 1] -= a[i][j] * a[i][j],
                a[i][j] *= -2.0;
        a[i][n] = 1;
    }
    gauss();
    for (int i = 1; i < n; ++i)
        printf("%.3lf ", a[i][n + 1]);
    return 0;
}