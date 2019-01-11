#include <iostream>
using namespace std;

const int Maxn = 20005;
int n, q, c[Maxn][2], prt[Maxn], aux[Maxn], rev[Maxn];

void pushdown(int x) {
    if (rev[x]) {
        rev[x] = 0;
        swap(c[x][0], c[x][1]);
        rev[c[x][0]] ^= 1;
        rev[c[x][1]] ^= 1;
    }
}

void rot(int x) {
    int y = prt[x], z = prt[y], L, r;
    L = (c[y][0] != x);
    r = L ^ 1;
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
    c[y][L] = c[x][r];
    c[x][r] = y;
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
        c[x][1] = y;
        prt[y] = x;
        aux[y] = 1;
        y = x;
        x = prt[x];
    }
}

void evert(int x) {
    access(x);
    splay(x);
    rev[x] ^= 1;
}

void link(int x, int y) {
    evert(y);
    prt[y] = x;
}

void cut(int x, int y) {
    evert(x);
    access(y);
    splay(y);
    prt[c[y][0]] = aux[c[y][0]] = 0;
    c[y][0] = 0;
}

int getroot(int x) {
    access(x);
    splay(x);
    int p = x;
    pushdown(p);
    while (c[p][0]) {
        p = c[p][0];
        pushdown(p);
    }
    return p;
}

void ask(int x, int y) {
    if (getroot(x) == getroot(y))
        cout << "Yes\n";
    else
        cout << "No\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y;
    string op;
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        cin >> op >> x >> y;
        if (op[0] == 'Q')
            ask(x, y);
        if (op[0] == 'C')
            link(x, y);
        if (op[0] == 'D')
            cut(x, y);
    }
    return 0;
}