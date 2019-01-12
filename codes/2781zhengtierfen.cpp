#include <iostream>
using namespace std;

const int inf = 0x7fffffff / 2;
const int Maxn = 200005;
struct node {
    int x, y, k, id, type;
} q[Maxn], q1[Maxn], q2[Maxn];
int n, m, tot, totx;
int c[Maxn], ans[Maxn], a[Maxn];

void add(int x, int z) {
    for (int i = x; i <= n; i += (i & (-i)))
        c[i] += z;
}

int ask(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= (i & (-i)))
        ans += c[i];
    return ans;
}

void divide(int ql, int qr, int l, int r) {
    if (ql > qr)
        return;
    if (l == r) {
        for (int i = ql; i <= qr; i++)
            if (q[i].type == 2)
                ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, t1 = 0, t2 = 0;
    for (int i = ql; i <= qr; i++) {
        if (q[i].type == 1) {
            if (q[i].x <= mid) {
                add(q[i].id, q[i].y);
                q1[t1++] = q[i];
            } else
                q2[t2++] = q[i];
        } else {
            int tt = ask(q[i].y) - ask(q[i].x - 1);
            if (tt >= q[i].k)
                q1[t1++] = q[i];
            else {
                q[i].k -= tt;
                q2[t2++] = q[i];
            }
        }
    }
    for (int i = 0; i < t1; i++)
        q[ql + i] = q1[i];
    for (int i = 0; i < t2; i++)
        q[ql + t1 + i] = q2[i];
    for (int i = 0; i < t1; i++)
        if (q1[i].type == 1)
            add(q1[i].id, -q1[i].y);
    divide(ql, ql + t1 - 1, l, mid);
    divide(ql + t1, qr, mid + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y, k;
    char op;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        a[i] = x;
        q[++tot].x = x;
        q[tot].y = 1;
        q[tot].type = 1;
        q[tot].id = i;
    }
    for (int i = 1; i <= m; i++) {
        cin >> op;
        if (op == 'Q') {
            cin >> x >> y >> k;
            q[++tot].x = x;
            q[tot].y = y;
            q[tot].k = k;
            q[tot].type = 2;
            q[tot].id = ++totx;
        } else {
            cin >> x >> y;
            tot++;
            q[tot].x = a[x];
            q[tot].y = -1;
            q[tot].type = 1;
            q[tot].id = x;
            a[x] = y;
            tot++;
            q[tot].x = y;
            q[tot].y = 1;
            q[tot].type = 1;
            q[tot].id = x;
        }
    }
    divide(1, tot, 0, inf);
    for (int i = 1; i <= totx; i++)
        cout << ans[i] << "\n";
    return 0;
}