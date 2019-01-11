#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 160005;

struct Edge {
    int to, next;
} edge[maxn * 2];

struct Bianji {
    int x, y, w;
} E[maxn * 2];

struct node {
    int l, r;
    int Max;
} tree[maxn * 3];

int head[maxn], tot, top[maxn], prt[maxn], dep[maxn], siz[maxn], p[maxn],
    fp[maxn], son[maxn];
int n, q, pos, Max;

void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void read() {
    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));
    cin >> n >> q;
    for (int i = 1; i <= n - 1; i++) {
        cin >> E[i].x >> E[i].y >> E[i].w;
        addedge(E[i].x, E[i].y);
        addedge(E[i].y, E[i].x);
    }
}

void dfs_1(int u, int pre, int d) {
    dep[u] = d;
    prt[u] = pre;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v != pre) {
            dfs_1(v, u, d + 1);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}

void dfs_2(int u, int sp) {
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if (son[u] != -1)
        dfs_2(son[u], sp);
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v != son[u] && v != prt[u])
            dfs_2(v, v);
    }
}

void build(int v, int L, int r) {
    tree[v].l = L;
    tree[v].r = r;
    tree[v].Max = 0;
    if (L == r)
        return;
    int mid = (L + r) / 2;
    build(2 * v, L, mid);
    build(2 * v + 1, mid + 1, r);
}

void pushup(int v) { tree[v].Max = max(tree[2 * v].Max, tree[2 * v + 1].Max); }

void insert(int v, int k, int val) {
    if (k < tree[v].l || k > tree[v].r)
        return;
    if (k == tree[v].l && k == tree[v].r) {
        tree[v].Max = val;
        return;
    }
    insert(2 * v, k, val);
    insert(2 * v + 1, k, val);
    pushup(v);
}

int query(int v, int L, int r) {
    if (L > tree[v].r || r < tree[v].l)
        return -(1 << 30);
    if (L <= tree[v].l && r >= tree[v].r)
        return tree[v].Max;
    return max(query(2 * v, L, r), query(2 * v + 1, L, r));
}

int lca(int u, int v) {
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while (f1 != f2) {
        if (dep[f1] < dep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query(1, p[f1], p[u]));
        u = prt[f1];
        f1 = top[u];
    }
    if (u == v)
        return tmp;
    if (dep[u] > dep[v])
        swap(u, v);
    return max(tmp, query(1, p[son[u]], p[v]));
}

void solve() {
    int op, u, v;
    for (int i = 1; i <= n - 1; i++) {
        if (dep[E[i].x] < dep[E[i].y])
            swap(E[i].x, E[i].y);
        insert(1, p[E[i].x], E[i].w);
    }
    for (int i = 1; i <= q; i++) {
        cin >> op >> u >> v;
        if (op == 0)
            insert(1, p[E[u].x], v);
        if (op == 1) {
            if (u == v)
                cout << -1 << "\n";
            else
                cout << lca(u, v) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    read();
    dfs_1(1, 0, 0);
    dfs_2(1, 1);
    build(1, 1, pos - 1);
    solve();
    return 0;
}
