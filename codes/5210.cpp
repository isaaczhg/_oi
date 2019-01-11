#include <algorithm>
#include <iostream>
using namespace std;

const int Maxn = 200005;
int n, m, num;
int c[Maxn], ans[Maxn];
struct node {
    int a, b, c, cnt, ans;
} a[Maxn], p[Maxn];

bool cmp1(const node &x, const node &y) {
    return (x.a < y.a || (x.a == y.a && x.b < y.b)) ||
           (x.a == y.a && x.b == y.b && x.c < y.c);
}
bool cmp2(const node &x, const node &y) {
    return (x.b < y.b) || (x.b == y.b && x.c < y.c);
}

inline int lowbit(int x) { return x & (-x); }

void add(int x, int d) {
    for (int i = x; i <= m; i += lowbit(i))
        c[i] += d;
    return;
}

int ask(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

void cdq(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    sort(p + l, p + mid + 1, cmp2);
    sort(p + mid + 1, p + r + 1, cmp2);
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (p[i].b <= p[j].b) {
            add(p[i].c, p[i].cnt);
            i++;
        } else {
            p[j].ans += ask(p[j].c);
            j++;
        }
    }
    while (j <= r) {
        p[j].ans += ask(p[j].c);
        j++;
    }
    for (j = l; j < i; j++)
        add(p[j].c, -p[j].cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int cnt = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i].a >> a[i].b >> a[i].c;
    sort(a + 1, a + n + 1, cmp1);
    for (int i = 1; i <= n; i++) {
        cnt++;
        if (a[i].a != a[i + 1].a || a[i].b != a[i + 1].b ||
            a[i].c != a[i + 1].c) {
            p[++num] = a[i];
            p[num].cnt = cnt;
            cnt = 0;
        }
    }
    cdq(1, num);
    for (int i = 1; i <= num; i++)
        ans[p[i].ans + p[i].cnt - 1] += p[i].cnt;
    for (int i = 0; i < n; i++)
        cout << ans[i] << "\n";
    return 0;
}