#include <iomanip>
#include <iostream>
using namespace std;

struct edge {
    int to, next;
} a[200005];

int n, sign = 0, scc = 0, top = 0, cnt = 0;
int f[200005][2], g[200005][2], fa[200005], p[200005], h[200005], ring[200005],
    prt[200005], belong[200005], dfn[200005], low[200005], stack[200005];
double k;

void addedge(int x, int y) {
    cnt++;
    a[cnt].to = y;
    a[cnt].next = h[x];
    h[x] = cnt;
}

void read() {
    int x, y;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        x++;
        y++;
        addedge(x, y);
        addedge(y, x);
    }
    cin >> k;
}

void tarjan(int x) {
    int y;
    dfn[x] = low[x] = ++sign;
    stack[++top] = x;
    for (int i = h[x]; i; i = a[i].next) {
        y = a[i].to;
        if (!dfn[y]) {
            fa[y] = x; //有向图，不能用instack
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (fa[x] != y)
            low[x] = min(low[x], dfn[y]);
    }
    int t;
    if (low[x] == dfn[x]) {
        if (stack[top] == x) {
            top--;
            return;
        }
        do {
            t = stack[top--];
            ring[++ring[0]] = t;
            belong[t] = 1;
        } while (t != x);
    }
}

void dp(int x) {
    int y;
    f[x][0] = 0;
    f[x][1] = p[x];
    for (int i = h[x]; i; i = a[i].next) {
        y = a[i].to;
        if (prt[x] != y && !belong[y]) {
            prt[y] = x;
            dp(y);
            f[x][0] += max(f[y][1], f[y][0]);
            f[x][1] += f[y][0];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    read();
    tarjan(1);
    int m = ring[0], ans = -0x7fffffff / 2;
    for (int i = 1; i <= m; i++)
        dp(ring[i]);
    for (int i = 1; i <= m; i++) {
        g[i][0] = f[ring[i]][0];
        g[i][1] = f[ring[i]][1];
    }
    // 1点不选
    f[2][0] = g[1][0] + g[2][0];
    f[2][1] = g[1][0] + g[2][1];
    for (int i = 3; i <= m; i++) {
        f[i][0] = max(f[i - 1][0], f[i - 1][1]) + g[i][0];
        f[i][1] = f[i - 1][0] + g[i][1];
    }
    ans = max(ans, max(f[m][0], f[m][1]));
    // 1点选
    f[2][0] = g[1][1] + g[2][0];
    f[2][1] = -0x7fffffff / 2;
    for (int i = 3; i <= m; i++) {
        f[i][0] = max(f[i - 1][0], f[i - 1][1]) + g[i][0];
        f[i][1] = f[i - 1][0] + g[i][1];
    }
    // for(int i=1;i<=m;i++)cout<<ring[i]<<endl;
    ans = max(ans, f[m][0]); //由于是环，因此1选m一定不选
    cout << fixed << setprecision(1) << double(ans) * k << "\n";
}