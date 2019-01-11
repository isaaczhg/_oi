#include <iostream>
using namespace std;

const int Maxn = 5005;

struct edge {
    int to, nx;
} e[Maxn];

int n, b, cnt, top, num;
int h[Maxn], root[Maxn], stack[Maxn], ans[Maxn];

void addedge(int x, int y) {
    e[++cnt].to = y;
    e[cnt].nx = h[x];
    h[x] = cnt;
}

void dfs(int x, int fa) {
    int last = top;
    for (int i = h[x]; i; i = e[i].nx) {
        int y = e[i].to;
        if (y == fa)
            continue;
        dfs(y, x);
        if (top - last >= b) {
            root[++num] = x;
            while (top > last)
                ans[stack[top--]] = num;
        }
    }
    stack[++top] = x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y;
    cin >> n >> b;
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        addedge(x, y);
        addedge(y, x);
    }
    dfs(1, 0);
    while (top)
        ans[stack[top--]] = num;
    cout << num << "\n";
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
    for (int i = 1; i <= num; i++)
        cout << root[i] << " ";
    cout << "\n";
    return 0;
}