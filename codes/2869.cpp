#include <iostream>
using namespace std;

const int Maxn = 200005;

int n, m, top;
int Q[Maxn], sum[Maxn], v[Maxn], rev[Maxn], p[Maxn], mark[Maxn], lc[Maxn],
    rc[Maxn], c[Maxn][2];

bool isroot(int x) { return c[p[x]][0] != x && c[p[x]][1] != x; }

void pushup(int x) {
    sum[x] = sum[c[x][0]] + sum[c[x][1]] + 1;
    if (c[x][0])
        sum[x] -= (rc[c[x][0]] == v[x]), lc[x] = lc[c[x][0]];
    else
        lc[x] = v[x];
    if (c[x][1])
        sum[x] -= (lc[c[x][1]] == v[x]), rc[x] = rc[c[x][1]];
    else
        rc[x] = v[x];
}

void updata(int x, int c) {
    if (!x)
        return;
    sum[x] = mark[x] = 1;
    lc[x] = rc[x] = v[x] = c;
}

void Rev(int x) {
    rev[x] ^= 1;
    swap(lc[c[x][0]], rc[c[x][0]]);
    swap(rc[c[x][1]], lc[c[x][1]]);
}

void push_down(int x) {
    int l = c[x][0], r = c[x][1];
    if (rev[x]) {
        rev[x] = 0;
        Rev(l);
        Rev(r);
        swap(c[x][0], c[x][1]);
    }
    if (mark[x]) {
        mark[x] = 0;
        updata(l, v[x]);
        updata(r, v[x]);
    }
}

void rotate(int x) {
    int y = p[x], z = p[y];
    if (!isroot(y))
        c[z][c[z][1] == y] = x;
    int l = c[y][1] == x, r = l ^ 1;

    p[x] = z;
    p[y] = x;
    p[c[x][r]] = y;

    c[y][l] = c[x][r];
    c[x][r] = y;
    pushup(y);
    pushup(x);
}

void splay(int x) {
    int top = 1;
    Q[top] = x;
    for (int t = x; !isroot(t); t = p[t])
        Q[++top] = p[t];
    while (top)
        push_down(Q[top--]);
    while (!isroot(x)) {
        int y = p[x], z = p[y];
        if (!isroot(y)) {
            if ((c[y][1] == x) ^ (c[z][1] == y))
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}

void access(int x) {
    for (int t = 0; x; t = x, x = p[x]) {
        splay(x);
        c[x][1] = t;
        pushup(x);
    }
}

void evert(int x) {
    access(x);
    splay(x);
    rev[x] ^= 1;
}

void link(int x, int y) {
    evert(x);
    p[x] = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y, z;
    char op;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        lc[i] = rc[i] = v[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        link(x, y);
    }
    for (int i = 1; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 'Q') {
            evert(y);
            access(x);
            splay(x);
            cout << sum[x] << "\n";
        } else {
            cin >> z;
            evert(y);
            access(x);
            splay(x);
            updata(x, z);
        }
    }
    return 0;
}