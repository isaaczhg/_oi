#include <iostream>
using namespace std;

const int inf = 0x7fffffff / 2;
const int Maxn = 200005;
struct node {
    int x, y, k, id, type;
} q[Maxn], q1[Maxn], q2[Maxn];
int n, m, tot;
int c[Maxn], ans[Maxn];


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

void divide(int ql, int qr, int L, int R) {
    if (ql > qr)
        return;
    if (L == R) {
        for (int i = ql; i <= qr; i++)
            if (q[i].type == 2)
                ans[q[i].id] = L;
        return;
    }
    int Mid = (L + R) >> 1;
    int t1 = 0, t2 = 0;
    for (int i = ql; i <= qr; i++) {
        if (q[i].type == 1) {
            if (q[i].x <= Mid) {
                add(q[i].id, 1);
                q1[++t1] = q[i];
            } else
                q2[++t2] = q[i];
        } else {
            int tt = ask(q[i].y) - ask(q[i].x - 1);
            if (tt >= q[i].k)
                q1[++t1] = q[i];
            else {
                q[i].k -= tt;
                q2[++t2] = q[i];
            }
        }
    }
    for (int i = 1; i <= t1; i++)
        if (q1[i].type == 1)
            add(q1[i].id, -1);
    for (int i = 1; i <= t1; i++)
        q[ql + i - 1] = q1[i];
    for (int i = 1; i <= t2; i++)
        q[ql + t1 + i - 1] = q2[i];
    divide(ql, ql + t1 - 1, L, Mid);
    divide(ql + t1, qr, Mid + 1, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    int x, y, k;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        tot++;
        q[tot].x = x;
        q[tot].type = 1;
        q[tot].id = i;
    }
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> k;
        tot++;
        q[tot].x = x;
        q[tot].y = y;
        q[tot].k = k;
        q[tot].type = 2;
        q[tot].id = i;
    }
    divide(1, tot, -inf, inf);
    for (int i = 1; i <= m; i++)
        cout << ans[i] << "\n";
    return 0;
}
