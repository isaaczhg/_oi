#include <iostream>
using namespace std;

const int maxn = 1000005;

struct heap {
    int bj, key, l, r, prt, id;
} a[maxn];
int n, m;

int getfather(int x) {
    if (a[x].prt == a[x].id)
        return a[x].id;
    a[x].prt = getfather(a[x].prt);
    return a[x].prt;
}

int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (a[x].key > a[y].key)
        swap(x, y);
    a[x].r = merge(a[x].r, y);
    swap(a[x].l, a[x].r);
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y, fx, fy;
    string op;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].key;
        a[i].id = i;
        a[i].prt = i;
        a[i].l = 0;
        a[i].r = 0;
        a[i].bj = 0;
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> op;
        if (op[0] == 'M') {
            cin >> x >> y;
            if (a[x].bj || a[y].bj)
                continue;
            fx = getfather(x);
            fy = getfather(y);
            if (fx == fy)
                continue;
            a[fx].prt = a[fy].prt = merge(fx, fy);
        } else {
            cin >> x;
            if (a[x].bj) {
                cout << "0\n";
                continue;
            }
            fx = getfather(x);
            a[fx].bj = 1;
            cout << a[fx].key << "\n";
            a[fx].prt = merge(a[fx].l, a[fx].r);
            a[a[fx].prt].prt = a[fx].prt;
        }
    }
    return 0;
}