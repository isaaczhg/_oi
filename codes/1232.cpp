#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

struct node {
    int x, y;
} a[1000005];

int maxx;
long long c[100005]= {0};

bool cmp(const node &x, const node &y) {
    return x.x < y.x || (x.x == y.x && x.y < y.y);
}
inline int lowbit(int x) { return x & (-x); }

long long sum(int x) {
    long long res = 0;
    for (int i = x; i <= maxx; i += lowbit(i))
        res += c[i];
    return res;
}

void add(int x) {
    for (int i = x; i > 0; i -= lowbit(i))
        c[i]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t, cas = 0, n, m, k;
    long long ans;
    cin >> t;
    while (t--) {
        ans = 0;
        cin >> n >> m >> k;
        for (int i = 1; i <= m; i++)
            c[i] = 0;
        maxx = m;
        for (int i = 1; i <= k; i++)
            cin >> a[i].x >> a[i].y;
        sort(a + 1, a + k + 1, cmp);
        for (int i = 1; i <= k; i++) {
            ans += sum(a[i].y + 1);
            add(a[i].y);
        }
        cout << "Test case " << ++cas << ": " << ans << '\n';
    }
    return 0;
}