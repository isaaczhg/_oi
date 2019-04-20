#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct node {
    int t, f, h;
} a[105];
int d, g;
int f[105];

bool cmp(const node &x, const node &y) {
    return x.t < y.t;
}

int main() {
    scanf("%d%d", &d, &g);
    for (int i = 1; i <= g; i++)
        scanf("%d%d%d", &a[i].t, &a[i].f, &a[i].h);
    sort(a + 1, a + g + 1, cmp);
    f[0] = 10;
    for (int i = 1; i <= g; i++) 
        for (int j = d; j >= 0; j--)
            if (f[j] >= a[i].t) {
                if (j + a[i].h >= d) {
                    printf("%d\n", a[i].t);
                    return 0;
                }
                f[j + a[i].h] = max(f[j + a[i].h], f[j]);
                f[j] += a[i].f;
            }
    printf("%d\n", f[0]);
    return 0;
}