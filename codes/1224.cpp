#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

struct stars {
    int x, y;
} a[100005];

int n, c[100005], ans[100005] = {0};

bool cmp(const stars &a, const stars &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

inline int lowbit(int x) { return x & (-x); }

void add(int x) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i]++;
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
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].x++;
        a[i].y++;
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        ans[sum(a[i].y)]++;
        add(a[i].y);
    }
    for (int i = 0; i <= n - 1; i++)
        cout << ans[i] << "\n";
    return 0;
}