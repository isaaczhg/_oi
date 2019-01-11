#include <cstring>
#include <iostream>
using namespace std;

const int Maxn = 100005;

int s[Maxn], c[3 * Maxn][2], ln[3 * Maxn], rn[3 * Maxn], v[3 * Maxn],
    prt[3 * Maxn], root[3 * Maxn], num[3 * Maxn];
int tmp, tot, m, n;

void rot(int x) {
    int y = prt[x], z = prt[y];
    int l = (c[y][0] != x), r = l ^ 1;
    if (z) {
        if (c[z][0] == y)
            c[z][0] = x;
        else
            c[z][1] = x;
    }
    prt[x] = z;
    prt[y] = x;
    prt[c[x][r]] = y;
    if (l) {
        rn[y] = ln[x];
        ln[x] = ln[y] + rn[y] + num[y];
    } else {
        ln[y] = rn[x];
        rn[x] = rn[y] + ln[y] + num[y];
    }
    c[y][l] = c[x][r];
    c[x][r] = y;
}

void splay(int k, int x) {
    while (prt[x]) {
        int y = prt[x], z = prt[y];
        if (z) {
            if (c[y][0] == x ^ c[z][0] == y)
                rot(x);
            else
                rot(y);
        }
        rot(x);
    }
    root[k] = x;
}

void add(int k, int x) {
    int p, f;
    p = root[k];
    while (p) {
        f = p;
        if (x == v[p]) {
            num[p]++;
            splay(k, p);
            return;
        }
        if (x < v[p]) {
            ln[p]++;
            p = c[p][0];
        } else if (x > v[p]) {
            rn[p]++;
            p = c[p][1];
        }
    }
    tot++;
    v[tot] = x;
    prt[tot] = 0;
    c[tot][1] = c[tot][0] = 0;
    ln[tot] = rn[tot] = 0;
    num[tot] = 1;
    if (root[k] == 0) {
        root[k] = tot;
        return;
    }
    prt[tot] = f;
    if (x < v[f])
        c[f][0] = tot;
    else
        c[f][1] = tot;
    splay(k, tot);
}

void found(int k, int d) {
    int p = root[k];
    while (p) {
        if (d == v[p]) {
            splay(k, p);
            return;
        }
        if (d < v[p])
            p = c[p][0];
        else
            p = c[p][1];
    }
}

void del(int v, int d) {
    found(v, d);
    int p = root[v];
    num[p]--;
    if (num[p])
        return;
    int ls = c[p][0], rs = c[p][1];
    if (!ls && !rs) {
        root[v] = 0;
        return;
    }
    if (!rs) {
        root[v] = ls;
        prt[ls] = 0;
        return;
    }
    if (!ls) {
        root[v] = rs;
        prt[rs] = 0;
        return;
    }
    p = ls;
    prt[ls] = 0;
    while (c[p][1])
        p = c[p][1];
    splay(v, p);
    c[p][1] = rs;
    prt[rs] = p;
    rn[p] = rn[rs] + ln[rs] + num[rs];
}

void exchange(int k, int l, int r, int x, int d, int a) {
    del(k, a);
    add(k, d);
    int mid = (l + r) >> 1;
    if (l == r)
        return;
    if (x <= mid)
        exchange(k << 1, l, mid, x, d, a);
    else
        exchange((k << 1) + 1, mid + 1, r, x, d, a);
}

void build(int v, int l, int r, int x, int sum) {
    add(v, sum);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        build(v << 1, l, mid, x, sum);
    else
        build((v << 1) + 1, mid + 1, r, x, sum);
}

void Find(int p, int x) {
    if (!p)
        return;
    if (v[p] <= x) {
        tmp += num[p] + ln[p];
        Find(c[p][1], x);
    } else
        Find(c[p][0], x);
}

void cal(int v, int l, int r, int x, int y, int sum) {
    if (l == x && r == y) {
        Find(root[v], sum);
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= y)
        cal(v << 1, l, mid, x, y, sum);
    else if (mid < x)
        cal((v << 1) + 1, mid + 1, r, x, y, sum);
    else {
        cal(v << 1, l, mid, x, mid, sum);
        cal((v << 1) + 1, mid + 1, r, mid + 1, y, sum);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y, z;
    char ch;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1; i <= n; i++)
        build(1, 1, n, i, s[i]);
    for (int i = 1; i <= m; i++) {
        cin >> ch;
        if (ch == 'C') {
            cin >> x >> y;
            exchange(1, 1, n, x, y, s[x]);
            s[x] = y;
        } else {
            cin >> x >> y >> z;
            int l = 0, r = 1000000000, ans;
            while (l <= r) {
                int mid = (l + r) >> 1;
                tmp = 0;
                cal(1, 1, n, x, y, mid);
                if (tmp >= z) {
                    ans = mid;
                    r = mid - 1;
                } else
                    l = mid + 1;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}