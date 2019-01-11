#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

const int Maxn = 100005;
struct edge {
    int to, nx;
} e[Maxn << 1];
int n, m, cnt, tot;
int h[Maxn], a[Maxn], root[Maxn], d[Maxn];
int p[Maxn][20], s[Maxn * 20], ch[Maxn * 20][2];

void init() {
    memset(h, 0, sizeof(h));
    memset(p, 0, sizeof(p));
    memset(s, 0, sizeof(s));
    memset(root, 0, sizeof(root));
    cnt = 0;
    tot = 0;
}

void addedge(int x, int y) {
    e[++cnt].to = y;
    e[cnt].nx = h[x];
    h[x] = cnt;
}

void read() {
    int x, y;
    init();
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        addedge(x, y);
        addedge(y, x);
    }
}

int insert(int x, int c) {
    int tmp, y;
    tmp = y = ++tot;
    for (int i = 15; i >= 0; i--) {
        ch[y][0] = ch[x][0];
        ch[y][1] = ch[x][1];
        s[y] = s[x] + 1;
        int t = (c >> i) & 1;
        x = ch[x][t];
        ch[y][t] = ++tot;
        y = ch[y][t];
    }
    s[y] = s[x] + 1;
    return tmp;
}

void dfs(int k, int depth) {
    d[k] = depth;
    root[k] = insert(root[p[k][0]], a[k]);
    for (int i = h[k]; i; i = e[i].nx)
        if (e[i].to != p[k][0]) {
            p[e[i].to][0] = k;
            dfs(e[i].to, depth + 1);
        }
}

void st() {
    for (int i = 1; i <= log2(n); i++)
        for (int j = 1; j <= n; j++)
            p[j][i] = p[p[j][i - 1]][i - 1];
}

int lca(int x, int y) {
    if (d[x] < d[y])
        swap(x, y);
    for (int i = log2(n); i >= 0; i--)
        if (p[x][i] && d[p[x][i]] >= d[y])
            x = p[x][i];
    if (x == y)
        return x;
    for (int i = log2(n); i >= 0; i--)
        if (p[x][i] != p[y][i]) {
            x = p[x][i];
            y = p[y][i];
        }
    return p[x][0];
}

int query(int x, int y, int z, int c) {
    int ans = 0;
    for (int i = 15; i >= 0; i--) {
        int t = (c >> i) & 1;
        if (s[ch[x][!t]] + s[ch[y][!t]] - 2 * s[ch[z][!t]] > 0) {
            x = ch[x][!t];
            y = ch[y][!t];
            z = ch[z][!t];
            ans = ans + (1 << i);
        } else {
            x = ch[x][t];
            y = ch[y][t];
            z = ch[z][t];
        }
    }
    return ans;
}

void solve() {
    int x, y, z, c;
    dfs(1, 1);
    st();
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> c;
        z = lca(x, y);
        cout << max(query(root[x], root[y], root[z], c), c ^ a[z]) << "\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n >> m) {
        read();
        solve();
    }
    return 0;
}
