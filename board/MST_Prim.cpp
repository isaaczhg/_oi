#include <iostream>
#include <cstdio>
using namespace std;

const int inf = 0x7fffffff;
int n, m, cnt, ans;
int h[1000005], d[1000005], vst[1000005];

struct edge {
    int to, next, v;
} a[1000005];

void addedge(int x, int y, int z) {
    a[++cnt].to = y;
    a[cnt].v = z;
    a[cnt].next = h[x];
    h[x] = cnt;
}

void prim(int x) {
    int minn, k;
    for (int i = 1; i <= n; i++)
        d[i] = inf;
    d[x] = 0;
    for (int i = 1; i <= n; i++) {
        minn = inf;
        for (int j = 1; j <= n; j++)
            if (!vst[j] && d[j] < minn) {
                k = j;
                minn = d[j];
            }
        /*if (minn == inf) {
            printf("No Solution!\n");
            return;
        }*/
        ans += d[k];
        vst[k] = 1;
        for (int t = h[k]; t; t = a[t].next) {
            int y = a[t].to;
            if (!vst[y] && a[t].v < d[y])
                d[y] = a[t].v;
            }
        }
    printf("%d\n", ans);
}

void read() {
    int x, y, z;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
}

int main() {
    read();
    prim(1);
    return 0;
}