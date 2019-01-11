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
    long long ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        l[i] = sum(a[i] - 1);
        add(a[i]);
    }
    memset(c, 0, sizeof(c));
    for (int i = n; i > 0; i--) {
        r[i] = sum(a[i] - 1);
        add(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        ans1 += l[i] * r[i];
        ans2 += (i - 1 - l[i]) * (n - i - r[i]);//比i大的为左右总数减去比i小的
    }
    cout << ans2 << " " << ans1 << "\n";
    return 0;
}