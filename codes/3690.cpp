#include <iostream>
using namespace std;

const int Maxn = 100005;

struct edge {
    int to, next;
} a[Maxn * 2];
struct Tree {
    int l, r, sum, bj;
} tree[Maxn * 20];
int n, m, h[Maxn], cnt, tot = -1;
int prt[Maxn], siz[Maxn], top[Maxn], ti[Maxn], son[Maxn], dep[Maxn];

void addedge(int x, int y) {
    cnt++;
    a[cnt].to = y;
    a[cnt].next = h[x];
    h[x] = cnt;
}

void read() {
    int x, y;
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        cin >> x >> y;
        addedge(x, y);
        addedge(y, x);
    }
}

void dfs_1(int u, int fa, int deep) {
    prt[u] = fa;
    siz[u] = 1;
    dep[u] = deep;
    for (int i = h[u]; i; i = a[i].next) {
        int to = a[i].to;
        if (to == fa)
            continue;
        dfs_1(to, u, deep + 1);
        siz[u] += siz[to];
        if (siz[to] > siz[son[u]])
            son[u] = to;
    }
}

void dfs_2(int u, int fa) {
    ti[u] = ++tot;
    if (son[prt[u]] != u)
        top[u] = u;
    else
        top[u] = top[prt[u]];
    if (son[u] != 0)
        dfs_2(son[u], u);
    for (int i = h[u]; i; i = a[i].next) {
        int to = a[i].to;
        if (to == fa || to == son[u])
            continue;
        dfs_2(to, u);
    }
}

void build(int u, int l, int r) {
    tree[u].l = l;
    tree[u].r = r;
    tree[u].sum = 0;
    tree[u].bj = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build((u << 1) + 1, mid + 1, r);
}

void pushdown(int u, int v) {
    tree[u].sum += (tree[u].r - tree[u].l + 1) * v;
    tree[u].bj += v;
}

void insert(int u, int l, int r) {
    if (tree[u].l > r || tree[u].r < l)
        return;
    if (tree[u].l >= l && tree[u].r <= r) {
        tree[u].sum += tree[u].r - tree[u].l + 1;
        tree[u].bj++;
        return;
    }
    if (tree[u].bj) {
        pushdown(u << 1, tree[u].bj);
        pushdown((u << 1) + 1, tree[u].bj);
        tree[u].bj = 0;
    }
    insert(u << 1, l, r);
    insert((u << 1) + 1, l, r);
    tree[u].sum = tree[u << 1].sum + tree[(u << 1) + 1].sum;
}

int ask(int u, int l, int r) {
    if (tree[u].l > r || tree[u].r < l)
        return 0;
    if (tree[u].l >= l && tree[u].r <= r)
        return tree[u].sum;
    if (tree[u].bj) {
        pushdown(u << 1, tree[u].bj);
        pushdown((u << 1) + 1, tree[u].bj);
        tree[u].bj = 0;
    }
    return ask(u << 1, l, r) + ask((u << 1) + 1, l, r);
}

void lca(int x, int y, bool bj) {
    int ret = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        if (bj)
            ret += ask(1, ti[top[x]], ti[x]);
        else
            insert(1, ti[top[x]], ti[x]);
        x = prt[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    if (bj) {
        ret += ask(1, ti[x] + 1, ti[y]);
        cout << ret << "\n";
    } else
        insert(1, ti[x] + 1, ti[y]);
}

void solve() {
    int x, y;
    char od;
    while (m--) {
        cin >> od >> x >> y;
        if (od == 'P')
            lca(x, y, 0);
        else
            lca(x, y, 1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    read();
    dfs_1(1, 1, 1);
    dfs_2(1, 1);
    build(1, 1, n - 1);
    solve();
    return 0;
}