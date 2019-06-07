#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

struct rec {
    int x, y;
    bool operator<(rec const &r) const { return y < r.y; }
};

set<rec> s;
set<rec>::iterator it, lt, rt;
int n, m, h[100005], g[100005];

bool cmp(int a, int b, int i) {
    return abs(h[a] - h[i]) < abs(h[b] - h[i]) ||
           (abs(h[a] - h[i]) == abs(h[b] - h[i]) && h[a] < h[b]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]);
    for (int i = 1, p; i <= n; i++) {
        rec r;
        r.x = i, r.y = h[i];
        s.insert(r);
        it = s.find(r);
        lt = rt = it;
        m = 0;
        if (lt != s.begin())
            g[++m] = (--(lt))->x;
        if (++rt != s.end())
            g[++m] = rt->x;
        if (i >= 2) {
            if (m < 2 || cmp(g[1], g[2], i))
                p = g[1];
            else
                p = g[2];
            printf("%d %d\n", abs(h[i] - h[p]), p);
        }
    }
    return 0;
}