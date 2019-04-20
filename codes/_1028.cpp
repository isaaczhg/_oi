#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int a[5005], f[5005], num[5005];
int n;

int main() {
    int maxx = 0, sum = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[i] < a[j])
                f[i] = max(f[i], f[j] + 1);
        }
        if (f[i] == 0)
            f[i] += 1;
        if (f[i] > maxx)
            maxx = f[i];
        for (int j = 1; j < i; j++) {
            if (f[i] == f[j] && a[i] == a[j])
                num[j] = 0;
            else if (f[i] == f[j] + 1 && a[i] < a[j])
                num[i] += num[j];
        }
        if (num[i] == 0)
            num[i] = 1;
    }
    for (int i = 1; i <= n; i++)
        if (f[i] == maxx)
            sum += num[i];
    printf("%d %d\n", maxx, sum);
    return 0;
}