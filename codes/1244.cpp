#include <iostream>
using namespace std;

int n, a[100005], b[100005], c[100005], h[100005];

inline int lowbit(int x) { return x & (-x); }

void add(int x, int d) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += d;
}

int sum(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int mid, l, r, summ, ans;
    cin >> n;
    a[1] = 0;
    for (int i = 2; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        add(i, 1);
    for (int i = n; i >= 1; i--) {
        l = 1;
        r = n;
        while (l <= r) {
            mid = (l + r) >> 1;
            summ = sum(mid);
            if (summ >= a[i] + 1) {
                ans = mid;
                r = mid - 1;
            } else
                l = mid + 1;
        }
        h[i] = ans;
        add(h[i], -1);
    }
    for (int i = 1; i <= n; i++)
        cout << h[i] << "\n";
    return 0;
}