#include <iostream>
using namespace std;

struct tree {
    int a, b, c, min;
} a[80000 * 4 + 1];
int minn, c, s, n;

void pushdown(int v) {
    if (a[v].c > 0) {
        a[v << 1].min -= a[v].c;
        a[(v << 1) + 1].min -= a[v].c;
        a[v << 1].c += a[v].c;
        a[(v << 1) + 1].c += a[v].c;
        a[v].c = 0;
    }
}

void pushup(int v) { a[v].min = min(a[v << 1].min, a[(v << 1) + 1].min); }

void find(int v, int l, int r) {
    if (l > a[v].b || r < a[v].a)
        return;
    if (l <= a[v].a && r >= a[v].b) {
        minn = min(minn, a[v].min);
        return;
    }
    pushdown(v);
    find(v << 1, l, r);
    find((v << 1) + 1, l, r);
    pushup(v);
}

void build(int v, int l, int r) {
    a[v].a = l;
    a[v].b = r;
    a[v].c = 0;
    a[v].min = s;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build((v << 1) + 1, mid + 1, r);
}

void modify(int v, int l, int r) {
    if (l > a[v].b || r < a[v].a)
        return;
    if (l <= a[v].a && r >= a[v].b) {
        a[v].min -= n;
        a[v].c += n;
        return;
    }
    pushdown(v);
    modify(v << 1, l, r);
    modify((v << 1) + 1, l, r);
    pushup(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int r, o, d;
    cin >> c >> s >> r;
    build(1, 1, c);
    for (int i = 1; i <= r; i++) {
        cin >> o >> d >> n;
        d--;
        minn = 0x7fffffff / 2;
        find(1, o, d);
        if (minn >= n) {
            cout << "YES\n";
            modify(1, o, d);
        } else
            cout << "NO\n";
    }
    return 0;
}