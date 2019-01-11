#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct node {
    int v, num;
} a[500005];

int n, b[500005], c[500005];

bool cmp(const node &a, const node &b) { 
    return a.v < b.v; 
}
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
    int maxx;
    long long ans;
    while (cin >> n) {
        if (!n)
            break;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].v;
            a[i].num = i;
        }
        sort(a + 1, a + n + 1, cmp);
        for (int i = 1; i <= n; i++) {
            b[a[i].num] = i;
        }
        memset(c, 0, sizeof(c));
        ans = 0;
        maxx = 0;
        for (int i = 1; i <= n; i++) {
            ans += sum(maxx) - sum(b[i]);
            add(b[i]);
            maxx = max(maxx, b[i]);
        }
        cout << ans << "\n";
    }
    return 0;
}