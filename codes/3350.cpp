#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn = 50005;

struct node {
    int l, r, id;
    long long a, b;
} a[Maxn];
int n, m, ans;
int c[Maxn], pos[Maxn], s[Maxn];

bool cmp(const node &x, const node &y) {
    return (x.l < y.l) || (x.l == y.l && x.r < y.r);
}

bool cmp2(const node &x, const node &y) { return x.id < y.id; }

void update(int p, int add) {
    ans -= s[c[p]] * s[c[p]];
    s[c[p]] += add;
    ans += s[c[p]] * s[c[p]];
    ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int blk, l, r;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    blk = int(sqrt(n));
    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / blk + 1;
    for (int i = 1; i <= m; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }
    sort(a + 1, a + m + 1, cmp);
    l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        for (; r < a[i].r; r++)
            update(r + 1, 1);
        for (; r > a[i].r; r--)
            update(r, -1);
        for (; l < a[i].l; l++)
            update(l, -1);
        for (; l > a[i].l; l--)
            update(l - 1, 1);
        if (a[i].l == a[i].r) {
            a[i].a = 0;
            a[i].b = 1;
            continue;
        }
        a[i].a = ans - (a[i].r - a[i].l + 1);
        a[i].b = (long long)(a[i].r - a[i].l + 1) * (a[i].r - a[i].l);
        long long k = __gcd(a[i].a, a[i].b);
        a[i].a /= k;
        a[i].b /= k;
    }
    sort(a + 1, a + m + 1, cmp2);
    for (int i = 1; i <= m; i++)
        cout << a[i].a << "/" << a[i].b << "\n";
    return 0;
}