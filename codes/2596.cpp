#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 200005;
int n, a[maxn];
long long c[maxn], l[maxn], r[maxn];

inline int lowbit(int x) { return x & (-x); }

void add(int x) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i]++;
}

long long sum(int x) {
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = n; i >= 1; i--) {
        r[i] = n - i - sum(a[i] - 1);
        ans += r[i] * (r[i] - 1) >> 1;
        add(a[i]);
    }
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; i++) {
        ans -= sum(a[i] - 1) * r[i];
        add(a[i]);
    }
    cout << ans << "\n";
    return 0;
}