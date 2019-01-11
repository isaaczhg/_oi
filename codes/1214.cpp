#include <cstdio>
#include <iostream>
using namespace std;

#define LL long long

struct node {
    LL lx, rx, ly, ry, lz, rz;
} a[1000005];

int w, h, n, cnt = 0;
LL ans;

void add(LL lx, LL ly, LL rx, LL ry, LL lz, LL rz) {
    cnt++;
    a[cnt].lx = lx;
    a[cnt].ly = ly;
    a[cnt].rx = rx;
    a[cnt].ry = ry;
    a[cnt].lz = lz;
    a[cnt].rz = rz;
}

void cut(int v, LL lx, LL ly, LL rx, LL ry, LL lz, LL rz, int cmd) {
    int lk, rk;
    if (cmd == 0) {
        lk = max(lx, a[v].lx);
        rk = min(rx, a[v].rx);
        if (a[v].lx < lk)
            add(a[v].lx, a[v].ly, lk, a[v].ry, a[v].lz, a[v].rz);
        if (a[v].rx > rk)
            add(rk, a[v].ly, a[v].rx, a[v].ry, a[v].lz, a[v].rz);
        cut(v, lk, ly, rk, ry, lz, rz, 1);
    }
    if (cmd == 1) {
        lk = max(ly, a[v].ly);
        rk = min(ry, a[v].ry);
        if (a[v].ly < lk)
            add(lx, a[v].ly, rx, lk, a[v].lz, a[v].rz);
        if (a[v].ry > rk)
            add(lx, rk, rx, a[v].ry, a[v].lz, a[v].rz);
        cut(v, lx, lk, rx, rk, lz, rz, 2);
    }
    if (cmd == 2) {
        lk = max(lz, a[v].lz);
        rk = min(rz, a[v].rz);
        if (a[v].lz < lk)
            add(lx, ly, rx, ry, a[v].lz, lk);
        if (a[v].rz > rk)
            add(lx, ly, rx, ry, rk, a[v].rz);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    LL lx, ly, rx, ry, lz, rz, x, y, z, r;
    int kind = 0;
    cin >> n;
    kind++;
    if (n == 0)
        return 1;
    ans = 0;
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y >> z >> r;
        lx = x - r;
        rx = x + r;
        ly = y - r;
        ry = y + r;
        lz = z - r;
        rz = z + r;
        for (int j = 1; j <= cnt; j++) {
            if (a[j].lx >= rx || a[j].ly >= ry || a[j].rx <= lx || a[j].ry <= ly || a[j].lz >= rz || a[j].rz <= lz)
                continue;
            cut(j, lx, ly, rx, ry, lz, rz, 0);
            a[j] = a[cnt];
            j--;
            cnt--;
        }
        add(lx, ly, rx, ry, lz, rz);
    }
    for (int i = 1; i <= cnt; i++)
        ans += (a[i].rx - a[i].lx) * (a[i].ry - a[i].ly) * (a[i].rz - a[i].lz);
    cout << ans << "\n";
    return 0;
}