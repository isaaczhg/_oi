#include <iostream>
using namespace std;

const int Maxn = 100005;

int n, q;
int v[Maxn], sum[Maxn], prt[Maxn], aux[Maxn], rev[Maxn], c[Maxn][2];

void pushdown(int x) {
    if (rev[x]) {
        rev[x] = 0;
        swap(c[x][0], c[x][1]);
        rev[c[x][0]] ^= 1;
        rev[c[x][1]] ^= 1;
    }
}

void pushup(int x) { sum[x] = v[x] + sum[c[x][0]] + sum[c[x][1]]; }

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
        pushup(x);
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

int findroot(int x) {
    access(x);
    splay(x);
    while (c[x][0]) {
        pushdown(x);
        x = c[x][0];
    }
    return x;
}

int getsum(int x, int y) {
    evert(x);
    access(y);
    splay(y);
    return sum[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y;
    string op;
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> v[i];
    cin >> q;
    while (q--) {
        cin >> op >> x >> y;
        if (op[0] == 'b') {
            if (findroot(x) == findroot(y))
                cout << "no\n";
            else {
                cout << "yes\n";
                link(y, x);
            }
        }
        if (op[0] == 'p') {
            access(x);
            splay(x);
            v[x] = y;
            pushup(x);
        }
        if (op[0] == 'e') {
            if (findroot(x) != findroot(y)) {
                cout << "impossible\n";
                continue;
            }
            cout << getsum(x, y) << "\n";
        }
    }
    return 0;
}