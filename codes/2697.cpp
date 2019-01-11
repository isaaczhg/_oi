#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 30005;

struct segment_tree {
    int l, r;
    int max, min, negate;
} tree[maxn * 3];

int head[maxn], Next[maxn << 1], ver[maxn << 1], top[maxn], prt[maxn],
    depth[maxn], num[maxn], p[maxn], fp[maxn], son[maxn], mat[maxn][3];
int tot, cnt;

inline void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void dfs1(int x, int p, int d) {
    depth[x] = d;
    prt[x] = p;
    num[x] = 1;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (y != p) {
            dfs1(y, x, d + 1);
            num[x] += num[y];
            if (son[x] == -1 || num[y] > num[son[x]])
                son[x] = y;
        }
    }
}

void dfs2(int x, int t) {
    top[x] = t;
    p[x] = cnt++;
    fp[p[x]] = x;
    if (!son[x])
        return;
    dfs2(son[x], t);
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (y != son[x] && y != prt[x])
            dfs2(y, y);
    }
}

void build(int i, int l, int r) {
    tree[i].l = l;
    tree[i].r = r;
    tree[i].max = tree[i].min = tree[i].negate = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build((i << 1) | 1, mid + 1, r);
}

void pushup(int i) {
    tree[i].min = min(tree[i << 1].min, tree[(i << 1) | 1].min);
    tree[i].max = max(tree[i << 1].max, tree[(i << 1) | 1].max);
}

void pushdown(int i) {
    if (tree[i].l == tree[i].r)
        return;
    if (tree[i].negate) {
        tree[i << 1].max = -tree[i << 1].max;
        tree[i << 1].min = -tree[i << 1].min;
        swap(tree[i << 1].max, tree[i << 1].min);
        tree[(i << 1) | 1].max = -tree[(i << 1) | 1].max;
        tree[(i << 1) | 1].min = -tree[(i << 1) | 1].min;
        swap(tree[(i << 1) | 1].max, tree[(i << 1) | 1].min);
        tree[i << 1].negate ^= 1;
        tree[(i << 1) | 1].negate ^= 1;
        tree[i].negate = 0;
    }
}

void update(int i, int k, int val) {
    if (tree[i].l == k && tree[i].r == k) {
        tree[i].max = tree[i].min = val;
        tree[i].negate = 0;
        return;
    }
    pushdown(i);
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (k <= mid)
        update(i << 1, k, val);
    else
        update((i << 1) | 1, k, val);
    pushup(i);
}

void nupdate(int i, int l, int r) {
    if (tree[i].l == l && tree[i].r == r) {
        tree[i].max = -tree[i].max;
        tree[i].min = -tree[i].min;
        swap(tree[i].max, tree[i].min);
        tree[i].negate ^= 1;
        return;
    }
    pushdown(i);
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (r <= mid)
        nupdate(i << 1, l, r);
    else if (l > mid)
        nupdate((i << 1) | 1, l, r);
    else {
        nupdate(i << 1, l, mid);
        nupdate((i << 1) | 1, mid + 1, r);
    }
    pushup(i);
}

int query(int i, int l, int r) {
    if (tree[i].l == l && tree[i].r == r)
        return tree[i].max;
    pushdown(i);
    int mid = (tree[i].l + tree[i].r) >> 1;
    if (r <= mid)
        return query(i << 1, l, r);
    else if (l > mid)
        return query((i << 1) | 1, l, r);
    else
        return max(query(i << 1, l, mid), query((i << 1) | 1, mid + 1, r));
    pushup(i);
}

int find(int x, int y) {
    int f1 = top[x], f2 = top[y], tmp = -100000000;
    while (f1 != f2) {
        if (depth[f1] < depth[f2]) {
            swap(f1, f2);
            swap(x, y);
        }
        tmp = max(tmp, query(1, p[f1], p[x]));
        x = prt[f1];
        f1 = top[x];
    }
    if (x == y)
        return tmp;
    if (depth[x] > depth[y])
        swap(x, y);
    return max(tmp, query(1, p[son[x]], p[y]));
}

void Negate(int x, int y) {
    int f1 = top[x], f2 = top[y];
    while (f1 != f2) {
        if (depth[f1] < depth[f2]) {
            swap(f1, f2);
            swap(x, y);
        }
        nupdate(1, p[f1], p[x]);
        x = prt[f1];
        f1 = top[x];
    }
    if (x == y)
        return;
    if (depth[x] > depth[y])
        swap(x, y);
    return nupdate(1, p[son[x]], p[y]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> mat[i][0] >> mat[i][1] >> mat[i][2];
        add(mat[i][0], mat[i][1]), add(mat[i][1], mat[i][0]);
    }
    dfs1(1, 0, 0);
    dfs2(1, 1);
    build(1, 0, cnt - 1);
    for (int i = 0; i < n - 1; i++) {
        if (depth[mat[i][0]] > depth[mat[i][1]])
            swap(mat[i][0], mat[i][1]);
        update(1, p[mat[i][1]], mat[i][2]);
    }
    string op;
    int x, y;
    while (cin >> op) {
        if (op[0] == 'D')
            break;
        cin >> x >> y;
        if (op[0] == 'Q')
            cout << find(x, y) << '\n';
        else if (op[0] == 'N')
            Negate(x, y);
        else
            update(1, p[mat[x - 1][1]], y);
    }
    return 0;
}
