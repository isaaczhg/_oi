#include <iostream>
#include <cstring>
using namespace std;

const int Maxn = 50005;

struct edge {
    int to, next;
} e[Maxn << 1];

int n, m, p, cnt;
int dep[Maxn], prt[Maxn], Size[Maxn], son[Maxn], tree[Maxn], top[Maxn],
    sum[Maxn], h[Maxn], v[Maxn];

inline int lowbit(int x) { return x & (-x); }

void addedge(int x, int y) {
    e[++cnt] = (edge){y, h[x]};
    h[x] = cnt;
}

void dfs_1(int x, int fa) {
    dep[x] = dep[fa] + 1;
    Size[x] = 1;
    for (int i = h[x]; i; i = e[i].next) {
        int y = e[i].to;
        if (y == fa)
            continue;
        prt[y] = x;
        dfs_1(y, x);
        Size[x] += Size[y];
        if (Size[son[x]] < Size[y])
            son[x] = y;
    }
}

void dfs_2(int x, int tp) {
    tree[x] = ++tree[0];
    top[x] = tp;
    if (son[x])
        dfs_2(son[x], top[x]);
    for (int i = h[x]; i; i = e[i].next) {
        int y = e[i].to;
        if (top[y])
            continue;
        dfs_2(y, y);
    }
}

int ask(int x) {
    int ret = 0;
    while (x) {
        ret += sum[x];
        x -= lowbit(x);
    }
    return ret;
}

void update(int x, int y) {
    while (x <= tree[0]) {
        sum[x] += y;
        x += lowbit(x);
    }
}

void add(int x, int y, int z) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(x, y);
            swap(fx, fy);
        }
        update(tree[fx], z);
        update(tree[x] + 1, -z);
        x = prt[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(tree[x], z);
    update(tree[y] + 1, -z);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b, x, y, z;
    char ch;
    while (cin >> n >> m >> p) {
        memset(sum, 0, sizeof(sum));
        memset(h, 0, sizeof(h));
        cnt = 0;
        for (int i = 1; i <= n; i++)
            cin >> v[i];
        for (int i = 1; i <= m; i++) {
            cin >> a >> b;
            addedge(a, b);
            addedge(b, a);
        }
        dfs_1(1, 1);
        dfs_2(1, 1);
        for (int i = 1; i <= n; i++) {
            update(tree[i], v[i]);
            update(tree[i] + 1, -v[i]);
        }
        for (int i = 1; i <= p; i++) {
            cin >> ch >> x;
            if (ch == 'I') {
                cin >> y >> z;
                add(x, y, z);
            } else if (ch == 'D') {
                cin >> y >> z;
                add(x, y, -z);
            } else {
                cout << ask(tree[x]) << "\n";
            }
        }
    }
    return 0;
}