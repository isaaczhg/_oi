#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn = 200005;

struct node {
    int l, r, lblk, rblk, num_c, id;
} q[Maxn];
struct modify {
    int x, y, front;
} c[Maxn];
int n, m, blk, cnt_q, cnt_c, l, r, head, ans;
int a[Maxn], b[Maxn], out[Maxn], cnt[Maxn * 100];

inline int getblock(int num) { return (num - 1) / blk + 1; }

bool cmp(node x, node y) {
    if (x.lblk == y.lblk) {
        if (x.rblk == y.rblk)
            return x.num_c < y.num_c;
        return x.rblk < y.rblk;
    }
    return x.lblk < y.lblk;
}

void update(int x, int d) {
    int tmp = cnt[a[x]];
    cnt[a[x]] += d;
    if (tmp == 0 && cnt[a[x]] == 1)
        ans++;
    else if (tmp == 1 && cnt[a[x]] == 0)
        ans--;
}

void change(int x, int color) {
    if (l <= x && x <= r) {
        cnt[a[x]]--;
        if (!cnt[a[x]])
            ans--;
        a[x] = color;
        if (!cnt[a[x]])
            ans++;
        cnt[a[x]]++;
    } else
        a[x] = color;
}

void mo() {
    l = 1, r = 0, head = 0;
    for (int i = 1; i <= cnt_q; i++) {
        while (head > q[i].num_c) {
            change(c[head].x, c[head].front);
            head--;
        }
        while (head < q[i].num_c) {
            head++;
            change(c[head].x, c[head].y);
        }
        while (r < q[i].r){
            r++;
            update(r, 1);
        }
        while (l > q[i].l) {
            l--;
            update(l, 1);
        }
        while (r > q[i].r) {
            update(r, -1);
            r--;
        }
        while (l < q[i].l) {
            update(l, -1);
            l++;
        }
        out[q[i].id] = ans;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    char op;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    blk = sqrt(n);
    for (int i = 1; i <= m; i++) {
        cin >> op;
        if (op == 'R') {
            cnt_c++;
            cin >> c[cnt_c].x >> c[cnt_c].y;
            c[cnt_c].front = b[c[cnt_c].x];
            b[c[cnt_c].x] = c[cnt_c].y;
        } else {
            cnt_q++;
            cin >> q[cnt_q].l >> q[cnt_q].r;
            q[cnt_q].id = cnt_q;
            q[cnt_q].lblk = getblock(q[cnt_q].l);
            q[cnt_q].rblk = getblock(q[cnt_q].r);
            q[cnt_q].num_c = cnt_c;
        }
    }
    sort(q + 1, q + cnt_q + 1, cmp);
    mo();
    for (int i = 1; i <= cnt_q; i++)
        cout << out[i] << "\n";
    return 0;
}