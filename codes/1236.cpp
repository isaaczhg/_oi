#include <iostream>
using namespace std;

int n, q, a[1000005];
long long c[1000005] = {0};

inline int lowbit(int x) { return x & (-x); }

void add(int x, int d) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += d;
}

long long sum(int x) {
    long long ans;
    ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int c, l, r, x;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= q; i++) {
        cin >> c;
        if (c == 1) {
            cin >> l >> r >> x;
            add(l, x);
            add(r + 1, -x);
        }
        if (c == 2) {
            cin >> x;
            cout << sum(x) + a[x] << "\n";
        }
    }
    return 0;
}