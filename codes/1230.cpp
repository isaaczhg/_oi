#include <iostream>
#include <cmath>
using namespace std;

#define LL long long
int const maxn = 100005;
int n;
LL a[maxn], c[maxn], prt[maxn];

inline int lowbit(int x) { return x & (-x); }

int getfather(int x) { 
    if (prt[x] == x)
        return x;
        else {
            prt[x] = getfather(prt[x]);
            return prt[x];
        }
}

void add(int x, LL d) {
    for (int i = x; i <= maxn; i += lowbit(i))
        c[i] += d;
    return;
}

LL sum(int x) {
    LL ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], add(i, a[i]), prt[i] = i;
    cin >> m;
    for (int i = 1, k, l, r; i <= m; i++) {
        cin >> k >> l >> r;
        if (k)
            cout << sum(r) - sum(l - 1) << '\n';
        else {
            for (int i = l, t; i <= r; i++) {
                i = getfather(i);
                if (i > r)
                    break;
                add(i, int(t = sqrt(a[i])) - a[i]);
                a[i] = t;
                if (a[i] == 1)
                    prt[i] = prt[i + 1];
            }
        }
    }
    return 0;
}
