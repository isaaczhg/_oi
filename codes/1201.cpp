#include <iostream>
using namespace std;

struct tree {
    int l, r, delta;
} a[4 * 100005 + 1];
int ans;

void build(int v, int l, int r) {
    int mid;
    a[v].l = l;
    a[v].r = r;
    a[v].delta = 0;
    if (l == r)
        return;
    mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build((v << 1) + 1, mid + 1, r);
}

void insert(int v, int l, int r) {
    if (a[v].l > r || a[v].r < l)
        return;
    if (a[v].l >= l && a[v].r <= r) {
        a[v].delta++;
        return;
    }
    if (a[v].l == a[v].r)
        return;
    insert(v << 1, l, r);
    insert((v << 1) + 1, l, r);
}

void ask(int v, int x) {
    if (x < a[v].l || x > a[v].r)
        return;
    ans += a[v].delta;
    if (a[v].l == a[v].r)
        return;
    ask(v << 1, x);
    ask((v << 1) + 1, x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, x, y, ord;
    cin >> n >> m;
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        cin >> ord;
        if (ord == 1) {
            cin >> x >> y;
            insert(1, x, y);
        }
        if (ord == 2) {
            cin >> x;
            ans = 0;
            ask(1, x);
            cout << ans % 2 << "\n";
        }
    }
    return 0;
}