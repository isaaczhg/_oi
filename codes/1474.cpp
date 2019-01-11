#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

const int Maxn = 200005;

struct edge {
    int to, nx;
} e[Maxn << 1];
int n, m, cnt;
int h[Maxn], d[Maxn], prt[Maxn], p[Maxn][20], sum[Maxn];

void addedge(int x, int y) {
    e[++cnt].to = y;
    e[cnt].nx = h[x];
    h[x] = cnt;
}

void dfs_1(int x, int deep) {
    d[x] = deep;
    for (int i = h[x]; i; i = e[i].nx)
        dfs_1(e[i].to, deep + 1);
}

void st() {
    memset(p, -1, sizeof(p));
    for (int i = 1; i <= n; i++)
        p[i][0] = prt[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i <= n; i++)
            if (p[i][j - 1] != -1)
                p[i][j] = p[p[i][j - 1]][j - 1];
}

int LCA(int a, int b) {
    int k;
    if (d[a] < d[b])
        swap(a, b);
    k = int(log2(d[a]));
    for (int i = k; i >= 0; i--)
        if (d[a] - (1 << i) >= d[b])
            a = p[a][i];
    if (a == b)
        return b;
    for (int i = k; i >= 0; i--)
        if (p[a][i] != -1 && p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    return p[a][0];
}

void dfs_2(int x, int fa) {
    for (int i = h[x]; i; i = e[i].nx) {
        int y = e[i].to;
        if (y == fa)
            continue;
        dfs_2(y, x);
        sum[x] += sum[y];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long ans = 0;
    int x, y;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        addedge(x, y);
        prt[y] = x;
    }
    dfs_1(1, 0);
    st();
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        int lca = LCA(x, y);
        sum[x]++;
        sum[y]++;
        sum[lca] -= 2;
    }
    dfs_2(1, 1);    
    for (int i = 2; i <= n; i++) {
        if (!sum[i])
            ans += m;
        else if (sum[i] == 1)
            ans++;
    }
    cout << ans << "\n";
    return 0;
}