#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 50005;
int n, a[maxn];
long long c[maxn], l[maxn], r[maxn];

inline int lowbit(int x) { return x & (-x); }

void add(int x) {
    for (int i = x; i <= maxn; i += lowbit(i)) //因为是用a[]中的值放入树状数组,上限为a中元素最大值
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
    for (int i = 1; i <= n; i++) {
        l[i] = sum(a[i] - 1);
        add(a[i]);
    }
    memset(c, 0, sizeof(c));
    for (int i = n; i > 0; i--) {
        r[i] = sum(a[i] - 1);
        add(a[i]);
    }
    for (int i = 1; i <= n; i++)
        ans += l[i] * r[i];
    cout << ans << " \n";
}