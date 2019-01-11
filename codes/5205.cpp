#include <iostream>
using namespace std;

const int Maxn  = 1000005;

int n, m, p, l, r, k, pos, tot, tmp, ans, top, L, R, mid;
int a[Maxn], father[Maxn], son[Maxn][2], Size[Maxn], val[Maxn];
struct tree {
    int l, r, root;
} t[Maxn];

void pushup(int x) {
    if (x)
        Size[x] = Size[son[x][0]] + Size[son[x][1]] + 1;
}

int leftmin(int x) {
    if (!son[x][0])
        return x;
    return leftmin(son[x][0]);
}

void newnode(int &x, int fa, int da) {
    if (top)
        x = top, top = 0;
    else
        x = ++tot;
    father[x] = fa;
    son[x][0] = son[x][1] = 0;
    val[x] = da;
    Size[x] = 1;
}

void rotate(int x, int k) {
    int y = father[x];
    son[y][!k] = son[x][k];
    father[son[y][!k]] = y;
    son[father[y]][son[father[y]][1] == y] = x;
    father[x] = father[y];
    son[x][k] = y;
    father[y] = x;
    pushup(y);
}

void splay(int x, int goal, int &root) {
    while (father[x] != goal) {
        int y = father[x], z = father[y], f = (son[z][0] == y);
        if (z == goal)
            rotate(x, son[y][0] == x);
        else {
            if (son[y][f] == x)
                rotate(x, !f);
            else
                rotate(y, f);
            rotate(x, f);
        }
    }
    pushup(x);
    if (!goal)
        root = x;
}

void kthfind(int x, int key) {
    if (!x)
        return;
    if (key <= val[x])
        kthfind(son[x][0], key);
    else {
        tmp += Size[son[x][0]] + 1;
        kthfind(son[x][1], key);
    }
}

int findit(int x, int key) {
    if (key < val[x])
        return findit(son[x][0], key);
    if (key == val[x])
        return x;
    return findit(son[x][1], key);
}

void insert(int &root, int key) {
    int x = root;
    if (!root) {
        newnode(root, 0, key);
        return;
    }
    while (son[x][key > val[x]])
        Size[x]++, x = son[x][key > val[x]];
    Size[x]++;
    newnode(son[x][key > val[x]], x, key);
    splay(son[x][key > val[x]], 0, root);
}

void del(int &root, int key) {
    int x = findit(root, key);
    splay(x, 0, root);
    top = root;
    if (!son[x][1]) {
        father[son[x][0]] = 0;
        root = son[x][0];
    } else {
        splay(leftmin(son[x][1]), root, root);
        son[son[root][1]][0] = son[root][0];
        father[son[root][1]] = 0;
        father[son[root][0]] = son[root][1];
        root = son[root][1];
    }
    pushup(root);
}

void pre(int x, int key) {
    if (!x)
        return;
    if (val[x] < key) {
        if (val[x] > ans)
            ans = val[x];
        pre(son[x][1], key);
    } else
        pre(son[x][0], key);
}

void suc(int x, int key) {
    if (!x)
        return;
    if (val[x] > key) {
        if (val[x] < ans)
            ans = val[x];
        suc(son[x][0], key);
    } else
        suc(son[x][1], key);
}

void change(int k, int x, int key, int last) {
    del(t[k].root, last);
    insert(t[k].root, key);
    int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
    if (l == r)
        return;
    if (x <= mid)
        change(k << 1, x, key, last);
    else
        change(k << 1 | 1, x, key, last);
}

void getk(int k, int x, int y, int key) {
    int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
    if (x == l && r == y)
        kthfind(t[k].root, key);
    else {
        if (x > mid)
            getk(k << 1 | 1, x, y, key);
        else if (y <= mid)
            getk(k << 1, x, y, key);
        else {
            getk(k << 1, x, mid, key);
            getk(k << 1 | 1, mid + 1, y, key);
        }
    }
}

void getpre(int k, int x, int y, int key) {
    int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
    if (x == l && r == y)
        pre(t[k].root, key);
    else {
        if (x > mid)
            getpre(k << 1 | 1, x, y, key);
        else if (y <= mid)
            getpre(k << 1, x, y, key);
        else
            getpre(k << 1, x, mid, key), getpre(k << 1 | 1, mid + 1, y, key);
    }
}

void getsuc(int k, int x, int y, int key) {
    int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
    if (x == l && r == y)
        suc(t[k].root, key);
    else {
        if (x > mid)
            getsuc(k << 1 | 1, x, y, key);
        else if (y <= mid)
            getsuc(k << 1, x, y, key);
        else
            getsuc(k << 1, x, mid, key), getsuc(k << 1 | 1, mid + 1, y, key);
    }
}

void build(int k, int l, int r) {
    t[k].l = l;
    t[k].r = r;
    for (int i = l; i <= r; i++)
        insert(t[k].root, a[i]);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    while (m--) {
        cin >> p;
        if (p != 3) {
            cin >> l >> r >> k;
            if (p == 1) {
                tmp = 1;
                getk(1, l, r, k);
                cout << tmp << "\n";
            } else if (p == 2) {
                L = 0;
                R = 0x7fffffff / 2;
                while (L <= R) {
                    mid = (L + R) >> 1;
                    tmp = 1;
                    getk(1, l, r, mid);
                    if (tmp <= k)
                        L = mid + 1, ans = mid;
                    else
                        R = mid - 1;
                }
                cout << ans << "\n";
            } else if (p == 4) {
                ans = -0x7fffffff / 2;
                getpre(1, l, r, k);
                cout << ans << "\n";
            } else if (p == 5) {
                ans = 0x7fffffff / 2;
                getsuc(1, l, r, k);
                cout << ans << "\n";
            }
        } else {
            cin >> pos >> k;
            change(1, pos, k, a[pos]);
            a[pos] = k;
        }
    }
    return 0;
}