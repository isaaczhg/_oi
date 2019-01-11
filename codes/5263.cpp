#include <iostream>
using namespace std;

const int Maxn = 2000005;

struct edge {
    int to, nx;
} e[Maxn << 1];

int n, m, r, cnt, num;
int s[Maxn], v[Maxn], h[Maxn], prt[Maxn], st[Maxn], ed[Maxn], sum[Maxn];

void addedge(int x, int y) {
    e[++cnt].to = y;
    e[cnt].nx = h[x];
    h[x] = cnt;
}

void dfs(int x, int fa) {
    st[x] = ++num;
    for (int i = h[x]; i; i = e[i].nx) {
        int y = e[i].to;
        if (y == fa)
            continue;
        dfs(y, x);
    }
    ed[x] = ++num;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y, op;
    long long ans = 0;
    cin >> n >> m >> r;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        addedge(x, y);
        addedge(y, x);
    }
    dfs(r, 0);
    for (int i = 1; i <= n; i++)
        v[st[i]] = s[i];
    while (m--) {
        cin >> op >> x;
        if (op == 1) {
            cin >> y;
            v[st[x]] += y;
        }
        else {
            ans = 0;
            for (int i = st[x]; i <= ed[x]; i++) {
                ans += v[i];
            }
            cout << ans << "\n";
        }
    }
    return 0;
}