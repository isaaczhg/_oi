#include <iostream>
using namespace std;

const int Maxn = 500005;

int n, m;
int Size[Maxn], sum[Maxn], prt[Maxn], aux[Maxn], rev[Maxn], c[Maxn][2];

void pushdown(int x) {
    if (rev[x]) {
        rev[x] = 0;
        swap(c[x][0], c[x][1]);
        rev[c[x][0]] ^= 1;
        rev[c[x][1]] ^= 1;
    }
}

void pushup(int x) { Size[x] = Size[c[x][1]] + Size[c[x][0]] + 1; }

void rot(int x) {
    int y = prt[x], z = prt[y], l, r;
    l = (c[y][0] != x);
    r = l ^ 1;
    if (aux[y]) {
        if (c[z][0] == y)
            c[z][0] = x;
        else
            c[z][1] = x;
    } else {
        aux[y] = 1;
        aux[x] = 0;
    }
    prt[x] = z;
    prt[y] = x;
    prt[c[x][r]] = y;
    c[y][l] = c[x][r];
    c[x][r] = y;
    pushup(y);
    pushup(x);
}

void splay(int x) {
    pushdown(x);
    while (aux[x]) {
        int y = prt[x], z = prt[y];
        if (aux[y])
            pushdown(z);
        pushdown(y);
        pushdown(x);
        if (aux[y]) {
            if (c[y][0] == x ^ c[z][0] == y)
                rot(x);
            else
                rot(y);
        }
        rot(x);
    }
}

void access(int x) {
    int y = 0;
    while (x) {
        splay(x);
        aux[c[x][1]] = 0;
        aux[y] = 1;
        c[x][1] = y;
        y = x;
        x = prt[x];
    }
}

int findroot(int x) {
    access(x);
    splay(x);
    while (c[x][0]) {
        pushdown(x);
        x = c[x][0];
    }
    return x;
}

void cut(int x) {
    access(x);
    splay(x);
    prt[c[x][0]] = 0;
    aux[c[x][0]] = 0;
    c[x][0] = 0;
    pushup(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int a, op, x, y;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        prt[i] = min(i + a, n + 1);
        Size[i] = 1;
    }
    Size[n + 1] = 1;
    cin >> m;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> x;
            x++;
            access(x);
            splay(x);
            cout << Size[c[x][0]] << "\n";
        } else {
            cin >> x >> y;
            x++;
            cut(x);
            prt[x] = min(x + y, n + 1);
            aux[x] = 0;
        }
    }
    return 0;
}