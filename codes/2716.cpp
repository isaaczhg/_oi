#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 30005;

struct Edge {
    int to, next;
} edge[maxn << 1];

struct node {
    int l, r, sum, Max;
} tree[maxn * 3];

int head[maxn], top[maxn], fa[maxn], deep[maxn], num[maxn], p[maxn], fp[maxn], son[maxn], s[maxn];
int pos, tot;

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));
}

void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs_1(int u, int pre, int d) {
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v != pre) {
            dfs_1(v, u, d + 1);
            num[u] += num[v];
            if (son[u] == -1 || num[v] > num[son[u]])
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
        if (v != son[u] && v != fa[u])
            dfs_2(v, v);
    }
}

void push_up(int i) {
    tree[i].sum = tree[i << 1].sum + tree[(i << 1) | 1].sum;
    tree[i].Max = max(tree[i << 1].Max, tree[(i << 1) | 1].Max);
}

void build(int i, int L, int r) {
    tree[i].l = L;
    tree[i].r = r;
    if (L == r) {
        tree[i].sum = tree[i].Max = s[fp[L]];
        return;
    }
    int mid = (L + r) / 2;
    build(i << 1, L, mid);
    build((i << 1) | 1, mid + 1, r);
    push_up(i);
}

void update(int i, int k, int val) {
    if (tree[i].l == k && tree[i].r == k) {
        tree[i].sum = tree[i].Max = val;
        return;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (k <= mid)
        update(i << 1, k, val);
    else
        update((i << 1) | 1, k, val);
    push_up(i);
}

int query_max(int i, int L, int r) {
    if (tree[i].l == L && tree[i].r == r)
        return tree[i].Max;
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (r <= mid)
        return query_max(i << 1, L, r);
    else if (L > mid)
        return query_max((i << 1) | 1, L, r);
    else
        return max(query_max(i << 1, L, mid),
                   query_max((i << 1) | 1, mid + 1, r));
}

int query_sum(int i, int L, int r) {
    if (tree[i].l == L && tree[i].r == r)
        return tree[i].sum;
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (r <= mid)
        return query_sum(i << 1, L, r);
    else if (L > mid)
        return query_sum((i << 1) | 1, L, r);
    else
        return query_sum(i << 1, L, mid) + query_sum((i << 1) | 1, mid + 1, r);
}

int find_max(int u, int v) {
    int f1 = top[u], f2 = top[v];
    int tmp = -0x7fffffff / 2;
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query_max(1, p[f1], p[u]));
        u = fa[f1];
        f1 = top[u];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return max(tmp, query_max(1, p[u], p[v]));
}

int find_sum(int u, int v) {
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp += query_sum(1, p[f1], p[u]);
        u = fa[f1];
        f1 = top[u];
    }
    if (deep[u] > deep[v])
        swap(u, v);
    return tmp + query_sum(1, p[u], p[v]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q, u, v;
    string op;
    cin >> n ;
    init();
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    dfs_1(1, 0, 0);
    dfs_2(1, 1);
    build(1, 0, pos - 1);
    cin >> q;
    while (q--) {
        cin >> op >> u >> v;
        if (op == "CHANGE")
            update(1, p[u], v);
        else if (op == "QMAX")
            cout << find_max(u, v) << "\n"; 
        else
           cout << find_sum(u, v) << "\n"; 
    }
    return 0;
}
