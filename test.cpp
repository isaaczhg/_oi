#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct bianji {
    int u, v, d;
} a[600005];
struct edge {
    int u, v, next;
}
int father[300005];
int n, m;
bool cmp(const bianji &x, const bianji &y) {
    return x.d < y.d;
}

int getfather(int x) {
    if (father[x] == x)
        return x;
    else return father[x] = getfather(father[x]);
}

void addedge(int x, int y, int d)

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) 
        scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].d);
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= n; i++)
        father[i] = i;
    long long cnt = 0ll;
    for(int i = 1; i <= m; i++) {
        int f1 = getfather(a[i].u);
        int f2 = getfather(a[i].v);
        if (f1 != f2) {
            cnt += a[i].d;
            father[f1] = f2;
            addedge(a[i].u, a[i].v, a[i].d);
        }
    }
}