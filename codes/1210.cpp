#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 1005;

struct segment_tree2 {
    struct segment_tree {
        int l, r, c;
    } f[maxn * 4 + 1];
    int l, r;
} a[maxn * 4 + 1];
int x1, x2, y1, y2, n, ans;

void build_y(int p, int v, int l, int r) {
    a[p].f[v].l = l;
    a[p].f[v].r = r;
    a[p].f[v].c = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build_y(p, v << 1, l, mid);
    build_y(p, (v << 1) | 1, mid + 1, r);
}

void build_x(int v, int l, int r) {
    a[v].l = l;
    a[v].r = r;
    build_y(v, 1, 1, n);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build_x(v << 1, l, mid);
    build_x((v << 1) | 1, mid + 1, r);
}

void add_y(int p, int v) {
    if (a[p].f[v].l > y2 || a[p].f[v].r < y1)
        return;
    if (y1 <= a[p].f[v].l && a[p].f[v].r <= y2) {
        a[p].f[v].c++;
        return;
    }
    if (a[p].f[v].l == a[p].f[v].r)
        return;
    add_y(p, v << 1);
    add_y(p, (v << 1) | 1);
}

void add_x(int v) {
    if (a[v].l > x2 || a[v].r < x1)
        return;
    if (x1 <= a[v].l && a[v].r <= x2) {
        add_y(v, 1);
        return;
    }
    add_x(v << 1);
    add_x((v << 1) | 1);
}

void ask_y(int p, int v) {
    if (a[p].f[v].l > y1 || y1 > a[p].f[v].r)
        return;
    if (a[p].f[v].l <= y1 && y1 <= a[p].f[v].r)
        ans += a[p].f[v].c;
    if (a[p].f[v].l == a[p].f[v].r)
        return;
    int mid = (a[p].f[v].l + a[p].f[v].r) >> 1;
    if (y1 <= mid)
        ask_y(p, v << 1);
    else
        ask_y(p, (v << 1) | 1);
}

void ask_x(int v) {
    if (a[v].l > x1 || x1 > a[v].r)
        return;
    if (a[v].l <= x1 && x1 <= a[v].r)
        ask_y(v, 1);
    if (a[v].l == a[v].r)
        return;
    int mid = (a[v].l + a[v].r) >> 1;
    if (x1 <= mid)
        ask_x(v << 1);
    else
        ask_x((v << 1) | 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, t;
    char ch;
    cin >> x;
    while (x--) {
        cin >> n >> t;
        build_x(1, 1, n);
        for (int j = 1; j <= t; j++) {
            cin >> ch;
            if (ch == 'C') {
                cin >> x1 >> y1 >> x2 >> y2;
                add_x(1);
            } 
            else {
                cin >> x1 >> y1;
                ans = 0;
                ask_x(1);
                cout << ans % 2 << '\n';
            }
        }
        cout << '\n';
    }
}