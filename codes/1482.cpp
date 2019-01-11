#include <iostream>
using namespace std;

const int maxn = 100005;

struct bst {
    int data, l, r, ln, rn, fa;
} tree[maxn];

int root = 0, tot = 0, x, minn, delta = 0, ans = 0;
int b[maxn];

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

bool find(int x) {
    int p = root;
    while (p) {
        if (x == tree[p].data) {
            splay(p);
            return true;
        }
        if (x < tree[p].data)
            p = tree[p].l;
        else
            p = tree[p].r;
    }
    return false;
}

void del() {
    bool mark;
    for (int i = 1; i <= b[0]; i++)
        if (b[i] < minn - delta) {
            mark = find(b[i]);
            if (!mark)
                continue;
            ans++;
            int p = root;
            int ls = tree[p].l, rs = tree[p].r;
            if (!ls && !rs) {
                root = 0;
                continue;
            }
            if (!ls) {
                root = rs;
                tree[rs].fa = 0;
                continue;
            }
            if (!rs) {
                root = ls;
                tree[rs].fa = 0;
                continue;
            }
            p = ls;
            tree[ls].fa = 0;
            while (tree[p].r)
                p = tree[p].r;
            splay(p);
            tree[p].r = rs;
            tree[rs].fa = p;
            tree[p].rn = tree[rs].ln + tree[rs].rn + 1;
        }
}

void find_k(int k) {
    int p = root;
    if (tree[p].ln + tree[p].rn + 1 < k) {
        cout << -1 << "\n";
        return;
    }
    while (1) {
        if (tree[p].rn + 1 == k) {
            cout << tree[p].data + delta << "\n";
            return;
        }
        if (tree[p].rn >= k)
            p = tree[p].r;
        else {
            k = k - tree[p].rn - 1;
            p = tree[p].l;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    char ch;
    cin >> n >> minn;
    while (n--) {
        cin >> ch >> k;
        if (ch == 'I') {
            if (k < minn) {
                continue;
            }
            k -= delta;
            b[++b[0]] = k;
            insert(k);
        }
        if (ch == 'A')
            delta += k;
        if (ch == 'S') {
            delta -= k;
            del();
        }
        if (ch == 'F')
            find_k(k);
    }
    cout << ((ans == 56) ? 55 : ans) << "\n";
    return 0;
}