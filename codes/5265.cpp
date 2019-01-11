#include <cmath>
#include <cstring>
#include <iostream>
#define LL long long
using namespace std;

const LL Maxn = 1000005;
LL h[Maxn], to[Maxn << 1], nx[Maxn << 1], st[Maxn], ed[Maxn], s[Maxn], v[Maxn], d[Maxn], prt[Maxn], p[Maxn][20];
LL c1[Maxn], c2[Maxn], v2[Maxn];
LL cnt, n, m, root, num;

template <typename T> inline void read(T &x) {
    LL d = 1;
    x = 0;
    char c = cin.get();
    while (c < '0' || c > '9') {
        if (c == '-')
            d = -1;
        c = cin.get();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = cin.get();
    }
    x *= d;
}

inline LL lowbit(LL x) { return x & (-x); }

void addedge(LL x, LL y) { 
    to[++cnt] = y;
    nx[cnt] = h[x];
    h[x] = cnt; 
}

void dfs(LL x, LL fa, LL deep) {
    d[x] = deep;
    st[x] = ++num;
    prt[x] = fa;
    v2[x] = v[x];
    for (LL i = h[x]; i; i = nx[i]) {
        LL y = to[i];
        if (y == fa)
            continue;
        dfs(y, x, deep + 1);
        v2[x] += v2[y];
    }
    ed[x] = num;
}

void add(LL c[], LL x, LL d) {
    for (LL i = x; i <= n + 1; i += lowbit(i))
        c[i] += d;
}

void ST() {
    memset(p, -1, sizeof(p));
    for (LL i = 1; i <= n; i++)
        p[i][0] = prt[i];
    for (LL j = 1; (1 << j) <= n; j++)
        for (LL i = 1; i <= n; i++)
            if (p[i][j - 1] != -1)
                p[i][j] = p[p[i][j - 1]][j - 1];
}

LL LCA(LL a, LL b) {
    LL k;
    if (d[a] < d[b])
        swap(a, b);
    k = int(log2(d[a]));
    for (LL i = k; i >= 0; i--)
        if (d[a] - (1 << i) >= d[b])
            a = p[a][i];
    if (a == b)
        return b;
    for (LL i = k; i >= 0; i--)
        if (p[a][i] != -1 && p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    return p[a][0];
}

LL sum(LL c[], LL x) {
    LL ans = 0;
    for (LL i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    read(n), read(m), read(root);
    addedge(root, n + 1);
    addedge(n + 1, root);
    for (LL i = 1; i <= n; i++)
        read(v[i]);
    for (LL i = 1, x, y; i < n; i++) {
        read(x);
        read(y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs(n + 1, 0, 0);
    ST();
    for (LL i = 1, cmd, a, b, x, lca; i <= m; i++) {
        read(cmd), read(a);
        if (cmd == 1) {
            read(b), read(x);
            lca = LCA(a, b);
            add(c1, st[a], x);
            add(c1, st[b], x);
            add(c1, st[lca], -x);
            add(c1, st[prt[lca]], -x);
            add(c2, st[a], x * d[a]);
            add(c2, st[b], x * d[b]);
            add(c2, st[lca], -x * d[lca]);
            add(c2, st[prt[lca]], -x * d[prt[lca]]);
        } else if (cmd == 2)
            cout << v[a] + sum(c1, ed[a]) - sum(c1, st[a] - 1) << "\n";
        else
            cout << v2[a] + sum(c2, ed[a]) - sum(c2, st[a] - 1) - (d[a] - 1) * (sum(c1, ed[a]) - sum(c1, st[a] - 1)) << "\n";
    }
    return 0;
}