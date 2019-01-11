#include <iostream>
using namespace std;

const int maxn = 80005 * 4 + 1;
int n, m;
struct linetree {
    int a, b, bj, s;
} a[maxn];

void pushdown(int v) {
    if (a[v].bj == -1) {
        a[v << 1].bj = -1;
        a[(v << 1) + 1].bj = -1;
        a[v << 1].s = a[(v << 1) + 1].s = 0;
        a[v].bj = 0;
    }
    if (a[v].bj == 1) {
        if (a[v].bj == 1) {
            a[v << 1].bj = 1;
            a[(v << 1) + 1].bj = 1;
            a[v << 1].s = a[v << 1].b - a[v << 1].a + 1;
            a[(v << 1) + 1].s = a[(v << 1) + 1].b - a[(v << 1) + 1].a + 1;
            a[v].bj = 0;
        }
    }
}

void pushup(int v) { a[v].s = a[v << 1].s + a[(v << 1) + 1].s; }

void del(int v, int l, int r) {
    if (l > a[v].b || r < a[v].a)
        return;
    if (a[v].bj == -1)
        return;
    if (l <= a[v].a && r >= a[v].b) {
        a[v].s = 0;
        a[v].bj = -1;
    }
    pushdown(v);
    del(v << 1, l, r);
    del((v << 1) + 1, l, r);
    pushup(v);
}

void build(int v, int l, int r) {
    a[v].a = l;
    a[v].b = r;
    a[v].bj = 0;
    a[v].s = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build((v << 1) + 1, mid + 1, r);
}

void insert(int v, int l, int r) {
    if (l > a[v].b || r < a[v].a)
        return;
    if (a[v].bj == 1)
        return;
    if (l <= a[v].a && r >= a[v].b) {
        a[v].bj = 1;
        a[v].s = a[v].b - a[v].a + 1;
        return;
    }
    pushdown(v);
    insert(v << 1, l, r);
    insert((v << 1) + 1, l, r);
    pushup(v);
}

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int c, x, y;
    cin >> n >> m;
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        cin >> c >> x >> y;
        y--;
        if (c == 1)
            insert(1, x, y);
        else
            del(1, x, y);
    }
    cout << a[1].s << "\n";
    return 0;
}
