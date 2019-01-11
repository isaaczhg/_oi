#include <iostream>
using namespace std;

const int maxn = 40005;

struct bst {
    int data, l, r, ln, rn, fa;
} tree[maxn];

int root = 0, tot = 0, x;

void zig(int x) {
    int y = tree[x].fa;
    tree[y].l = tree[x].r;
    if (tree[x].r)
        tree[tree[x].r].fa = y;
    tree[x].fa = tree[y].fa;
    if (tree[y].fa) {
        if (y == tree[tree[y].fa].l)
            tree[tree[y].fa].l = x;
        else
            tree[tree[y].fa].r = x;
    }
    tree[x].r = y;
    tree[y].fa = x;
    tree[y].ln = tree[x].rn;
    tree[x].rn = tree[y].ln + tree[y].rn + 1;
}

void zag(int x) {
    int y = tree[x].fa;
    tree[y].r = tree[x].l;
    if (tree[x].l)
        tree[tree[x].l].fa = y;
    tree[x].fa = tree[y].fa;
    if (tree[y].fa) {
        if (y == tree[tree[y].fa].l)
            tree[tree[y].fa].l = x;
        else
            tree[tree[y].fa].r = x;
    }
    tree[x].l = y;
    tree[y].fa = x;
    tree[y].rn = tree[x].ln;
    tree[x].ln = tree[y].ln + tree[y].rn + 1;
}

void splay(int x) {
    int p;
    while (tree[x].fa) {
        p = tree[x].fa;
        if (!tree[p].fa) {
            if (x == tree[p].l)
                zig(x);
            else
                zag(x);
            break;
        }
        if (x == tree[p].l) {
            if (p == tree[tree[p].fa].l) {
                zig(p);
                zig(x);
            } else {
                zig(x);
                zag(x);
            }
        } else {
            if (p == tree[tree[p].fa].r) {
                zag(p);
                zag(x);
            } else {
                zag(x);
                zig(x);
            }
        }
    }
    root = x;
}

void insert(int x) {
    int p, f;
    p = root;
    while (p) {
        f = p;
        if (x <= tree[p].data) {
            tree[p].ln++;
            p = tree[p].l;
        } else {
            tree[p].rn++;
            p = tree[p].r;
        }
    }
    tot++;
    tree[tot].data = x;
    tree[tot].fa = 0;
    tree[tot].l = 0;
    tree[tot].r = 0;
    tree[tot].ln = 0;
    tree[tot].rn = 0;
    if (!root) {
        root = tot;
        return;
    }
    tree[tot].fa = f;
    if (x <= tree[f].data)
        tree[f].l = tot;
    else
        tree[f].r = tot;
    splay(tot);
}

void find(int k) {
    int p = root;
    if (tree[p].ln + tree[p].rn + 1 < x)
        return;
    while (1) {
        if (tree[p].rn + 1 == k)
            return;
        if (tree[p].rn >= k)
            p = tree[p].r;
        else {
            k = k - tree[p].rn - 1;
            p = tree[p].l;
        }
    }
}

int pred() {
    find(x);
    int p = tree[root].l;
    while (p) {
        if (!tree[p].r)
            break;
        p = tree[p].r;
    }
    if (p)
        return tree[p].data;
    return -1;
}

int succ() {
    find(x);
    int p = tree[root].r;
    while (p) {
        if (!tree[p].l)
            break;
        p = tree[p].l;
    }
    if (p)
        return tree[p].data;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k, x1, x2, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        insert(k);
        if (tot >= 2) {
            x = 0x7fffffff / 2;
            x1 = pred();
            if (x1 != -1)
                x = k - x1;
            x2 = succ();
            if (x2 != -1)
                x = min(x, x2 - k);
            ans += x;
        } else
            ans += k;
    }
    cout << ans << "\n";
    return 0;
}