#include <algorithm>
#include <iostream>
using namespace std;

struct node {
    long long x, y;
    bool operator<(node const &n) const {
        return (x < n.x) || (x == n.x && y < n.y);
    }
} a[200005];

const int P1 = 31, P2 = 43, Q1 = 1000000007, Q2 = 1000000009;
long long sum1[200005], sum2[200005];
long long n, m, tot = 0, s1 = 1, s2 = 1;
string s;

int main() {
    long long ans = 1;
    cin >> n >> m >> s;
    s = ' ' + s;
    for (int i = 1; i <= m; i++)
        s1 = s1 * P1 % Q1, s2 = s2 * P2 % Q2;
    for (int i = 1; i <= n; i++) {
        sum1[i] = (sum1[i - 1] * P1 + s[i]) % Q1;
        sum2[i] = (sum2[i - 1] * P2 + s[i]) % Q2;
    }
    for (int i = m; i <= n; i++) {
        a[++tot].x = ((sum1[i] - sum1[i - m] * s1) % Q1 + Q1) % Q1;
        a[tot].y = ((sum2[i] - sum2[i - m] * s2) % Q2 + Q2) % Q2;
    }
    sort(a + 1, a + tot + 1);
    for (int i = 2; i <= tot; i++)
        if ((a[i].x != a[i - 1].x) || (a[i].y != a[i - 1].y))
            ans++;
    cout << ans << '\n';
    return 0;
}
