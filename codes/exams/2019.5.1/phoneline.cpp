//二分最小边权，类最短路求可行路径上大于mid值的边数，满足k则证明可行，往下分，找到mid最小值
#include <cstdio>
#include <iostream>
using namespace std;

const int Maxn = 10005;
struct edge {
    int to, nxt, v;
} e[Maxn * 2];
int h[Maxn * 2], d[Maxn], q[Maxn * 2];
int n, p, k, maxd, cnt;
bool vst[Maxn];

void addedge(int x, int y, int z) {
    e[++cnt].to = y;
    e[cnt].v = z;
    e[cnt].nxt = h[x];
    h[x] = cnt;
}

bool spfa(int v0, int lim) {
    int l = 0, r = 0, x, y;
    for (int i = 1; i <= n; i++)
        d[i] = 0x7fffffff / 2;
    d[v0] = 0;
    q[++r] = v0;
    vst[v0] = 1;
    while (l != r) {
        l = (l + 1) % 200000;
        int i = q[l];
        vst[i] = 0;
        for (x = h[i]; x; x = e[x].nxt) {
            int j = e[x].to;
            if (e[x].v > lim)
                y = 1;
            else
                y = 0;
            if (d[j] > d[i] + y) {
                d[j] = d[i] + y;
                if (vst[j] == 0) {
                    r = (r + 1) % 200000;
                    q[r] = j;
                    vst[j] = 1;
                }
            }
        }
    }
    if (d[n] <= k)
        return true;
    else
        return false;
}

int main() {
    // freopen("phoneline.in", "r", stdin);
    // freopen("phoneline.out", "w", stdout);
    int x, y, z, l, r, ans;
    scanf("%d%d%d", &n, &p, &k);
    for (int i = 1; i <= p; i++) {
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
        maxd = max(maxd, z);
    }
    l = 0, r = maxd;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (spfa(1, mid)) { //二分满足条件的最小值
            ans = mid;
            r = mid - 1;
        } else
            l = mid + 1;
    }
    if (spfa(1, ans))
        printf("%d\n", ans);
    else
        printf("-1\n");
    return 0;
}