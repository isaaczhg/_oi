#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100005;

struct bianji {
    int x, y, v;
} a[maxn];

int n, m, ans, bj = 1;
int prt[maxn];

bool cmp(const bianji &x, const bianji &y) { return x.v < y.v; }

int getfather(int x) {
    if (prt[x] == x)
        return x;
    prt[x] = getfather(prt[x]);
    return prt[x];
}

void read() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)//边集表示
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].v);
    sort(a + 1, a + m + 1, cmp);
}

void kruskal() {
    int f1, f2, k = 0;
    for (int i = 1; i <= n; i++)
        prt[i] = i;
    for (int i = 1; i <= m; i++)
    {
        f1 = getfather(a[i].x);
        f2 = getfather(a[i].y);
        if (f1 != f2) //证明没被连在一起，即在两个集合中
        {
            ans += a[i].v;
            prt[f1] = f2;
            k++;
            if (k == n - 1) {
                bj = 0;
                return;
            }
        }
    }
}

int main() {
    read();
    kruskal();
    if (!bj)
        printf("%d", ans);
    // else printf("Impossible");
    return 0;
}