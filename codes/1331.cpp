#include <iostream>
using namespace std;

const int Maxn = 100005;

int c[Maxn][2], fa[Maxn], mx[Maxn], v[Maxn], s[Maxn], t[Maxn], re[Maxn];
int n, m, rt;

void pushup(int x) {
    int l = c[x][0], r = c[x][1];
    s[x] = s[l] + s[r] + 1;
    mx[x] = max(v[x], max(mx[l], mx[r]));
}

void pushdown(int x) {
    int l = c[x][0], r = c[x][1];
    if (t[x] != 0) {
        if (l) {
            mx[l] += t[x];
            v[l] += t[x];
            t[l] += t[x];
        }
        if (r) {
            mx[r] += t[x];
            v[r] += t[x];
            t[r] += t[x];
        }
        t[x] = 0;
    }
    if (re[x]) {
        re[x] = 0;
        re[l] ^= 1;
        re[r] ^= 1;
        swap(c[x][0], c[x][1]);
    }
}

void rot(int x, int &f) {
    int y = fa[x], z = fa[y], l, r;
    l = (c[y][0] != x);
    r = l ^ 1;
    if (y == f)
        f = x;
    else {
        if (c[z][0] == y)
            c[z][0] = x;
        else
            c[z][1] = x;
    }
    fa[x] = z;
    fa[y] = x;
    fa[c[x][r]] = y;
    c[y][l] = c[x][r];
    c[x][r] = y;
    pushup(y);
    pushup(x);
}

void splay(int x, int &f) {
    while (x != f) {
        int y = fa[x], z = fa[y];
        if (y != f) {
            if (c[y][0] == x ^ c[z][0] == y)
                rot(x, f);
            else
                rot(y, f);
        }
        rot(x, f);
    }
}

int find(int x, int k) {
    pushdown(x);
    int l = c[x][0], r = c[x][1];
    if (s[l] + 1 == k)
        return x;
    if (s[l] >= k)
        return find(l, k);
    return find(r, k - s[l] - 1);
}

void add(int l, int r, int z) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt);
    splay(y, c[x][1]);
    t[x = c[y][0]] += z;
    v[x] += z;
    mx[x] += z;
}

void rev(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt);
    splay(y, c[x][1]);
    re[c[y][0]] ^= 1;
}

void Max(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt);
    splay(y, c[x][1]);
    cout << mx[c[y][0]] << "\n";
}

int build(int l, int r) {
    int mid = (l + r) >> 1;
    if (l > r)
        return 0;
    c[mid][0] = build(l, mid - 1);
    if (c[mid][0])
        fa[c[mid][0]] = mid;
    c[mid][1] = build(mid + 1, r);
    if (c[mid][1])
        fa[c[mid][1]] = mid;
    pushup(mid);
    return mid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int k, x, y, z;
    cin >> n >> m;
    rt = build(1, n + 2);
    mx[0] = -0x7fffffff / 2;
    for (int i = 1; i <= m; i++) {
        cin >> k >> x >> y;
        if (k == 1) {
            cin >> z;
            add(x, y, z);
        } else if (k == 2)
            rev(x, y);
        else
            Max(x, y);
    }
    return 0;
}