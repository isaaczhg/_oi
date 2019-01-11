#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int const Maxn = 100005;
int a[Maxn], tmp[Maxn], pos[Maxn], ans[Maxn], c[Maxn];
int n, m, blk;

struct node {
    int l, r, id;
}q[Maxn];

bool operator<(const node &x, const node &y) {
    if (pos[x.l] == pos[y.l])
        return x.r < y.r;
    return pos[x.l] < pos[y.l];
}

inline int lowbit(int x) { return x & (-x); }

void add(int x, int d) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += d;
}

int sum(int x) {
    int ret = 0;
    for (int i = x; i; i -= lowbit(i))
        ret += c[i];
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], tmp[i] = a[i];
    sort(tmp + 1, tmp + n + 1);
    int tot = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(tmp + 1, tmp + tot + 1, a[i]) - tmp;
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> q[i].l >> q[i].r, q[i].id = i;
    blk = (int)sqrt(n);
    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / blk + 1;
    sort(q + 1, q + m + 1);
    int l = q[1].l, r = q[1].r, tmp = 0;
    for (int i = r; i >= l; i--)
        tmp += sum(a[i]), add(a[i], 1);
    ans[q[1].id] = tmp;
    for (int i = 2; i <= m; i++) {
        while (l < q[i].l) {
            add(a[l], -1);
            tmp -= sum(a[l] - 1);
            l++;
        }
        while (r > q[i].r) {
            add(a[r], -1);
            tmp -= r - l - sum(a[r]);
            r--;
        }
        while (l > q[i].l) {
            tmp += sum(a[--l] - 1);
            add(a[l], 1);
        }
        while (r < q[i].r) {
            r++;
            tmp += r - l - sum(a[r]);
            add(a[r], 1);
        }
        ans[q[i].id] = tmp;
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
    return 0;
}