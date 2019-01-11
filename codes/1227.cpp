#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 100005;
int c[maxn], n;

int lowbit(int x) { return x & (-x); }

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
    int l, r;
    while (1) {
        cin >> n;
        if (n == 0)
            break;
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++) {
            cin >> l >> r;
            add(l, 1);
            add(r + 1, -1);
        }
        for (int i = 1; i < n; i++)
            cout << sum(i) << " ";
        cout << sum(n) << "\n";
    }
    return 0;
}