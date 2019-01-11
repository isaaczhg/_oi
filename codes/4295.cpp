#include <iostream>
using namespace std;

const int Maxn = 100005;
int tree[Maxn][2], v[Maxn], fa[Maxn], mx[Maxn], s[Maxn], sum[Maxn],
    pos[Maxn], tag[Maxn], rev[Maxn];
int n, m, sz = 0, rt = 0;

void pushup(int x) {
    int l = tree[x][0], r = tree[x][1];
    mx[x] = max(max(mx[l], mx[r]), v[x]);
    sum[x] = sum[l] + sum[r] + v[x];
    s[x] = s[l] + s[r] + 1;
}

void pushdown(int x) {
    int l = tree[x][0], r = tree[x][1];
    if (tag[x]) {
        if (l) {
            tag[l] += tag[x];
            mx[l] += tag[x];
            v[l] += tag[x];
        }
        if (r) {
            tag[r] += tag[x];
            mx[r] += tag[x];
            v[r] += tag[x];
        }
        tag[x] = 0;
    }
    if (rev[x]) {
        rev[x] = 0;
        rev[l] ^= 1;
        rev[r] ^= 1;
        swap(tree[x][0], tree[x][1]);
    }
}

void rot(int x, int &f) {
    int y = fa[x], z = fa[y], l, r;
    l = (tree[y][0] != x);
    r = l ^ 1;
    if (y == f)
        f = x;
    else {
        if (tree[z][0] == y)
            tree[z][0] = x;
        else
            tree[z][1] = x;
    }
    fa[x] = z;
    fa[y] = x;
    fa[tree[x][r]] = y;
    tree[y][l] = tree[x][r];
    tree[x][r] = y;
    pushup(y);
    pushup(x);
}

void splay(int x, int &f) {
    while (x != f) {
        int y = fa[x], z = fa[y];
        if (y != f) {
            if (tree[y][0] == x ^ tree[z][0] == y)
                rot(x, f);
            else
                rot(y, f);
        }
        rot(x, f);
    }
}

int find(int x, int k) {
    pushdown(x);
    int l = tree[x][0], r = tree[x][1];
    if (s[l] + 1 == k)
        return x;
    if (s[l] >= k)
        return find(l, k);
    else
        return find(r, k - s[l] - 1);
}

void ask(int l) {
    int x = find(rt, l + 1);
    splay(x, rt);
    cout << v[rt] << "\n";
}

void add(int l, int z) {
    int x = find(rt, l), y = find(rt, l + 2);
    splay(x, rt);
    splay(y, tree[rt][1]);
    tag[tree[y][0]] += z;
    v[tree[y][0]] += z;
    mx[tree[y][0]] += z;
    sum[tree[y][0]] += z;
}

void Max(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt);
    splay(y, tree[rt][1]);
    cout << mx[tree[y][0]] << "\n";
}

void Rev(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt);
    splay(y, tree[rt][1]);
    rev[tree[y][0]] ^= 1;
}

void Sum(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt);
    splay(y, tree[rt][1]);
    cout << sum[tree[y][0]] << "\n";
}

int build(int l, int r) {
    int mid = (l + r) / 2;
    if (l > r)
        return 0;
    tree[mid][0] = build(l, mid - 1);
    if (tree[mid][0])
        fa[tree[mid][0]] = mid;
    tree[mid][1] = build(mid + 1, r);
    if (tree[mid][1])
        fa[tree[mid][1]] = mid;
    pushup(mid);
    return mid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int k, x, y;
    cin >> n >> m;
    mx[0] = -0x7fffffff / 2;
    for (int i = 1; i <= n; i++)
        cin >> v[i + 1];
    rt = build(1, n + 2);
    for (int i = 1; i <= m; i++) {
        cin >> k >> x;
        if (k == 1) {
            ask(x);
            continue;
        }
        cin >> y;
        if (k == 2)
            add(x, y);
        if (k == 3)
            Sum(x, y);
        if (k == 4)
            Max(x, y);
        if (k == 5)
            Rev(x, y);
    }
    return 0;
}
