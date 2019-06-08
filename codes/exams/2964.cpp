#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

struct work {
    int t, w;
} a[1000005];
int f[1000005];
int n, f1, ans;

bool cmp(const work &a, const work &b) { return a.w > b.w; }

int getfather(int x) {
    if (x == 0)
        return -1;
    if (f[x] == x)
        return x;
    f[x] = getfather(f[x]);
    return f[x];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n - 1; i++)
        scanf("%d%d", &a[i].t, &a[i].w);
    sort(a, a + n, cmp);
    for (int i = 0; i <= 1000005; i++)
        f[i] = i;
    for (int i = 0; i <= n - 1; i++) {
        f1 = getfather(a[i].t);
        if (f1 == -1)
            continue;
        else {
            f[f1] = getfather(f[f1 - 1]);
            ans += a[i].w;
        }
    }
    printf("%d\n", ans);
    return 0;
}