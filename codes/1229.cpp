#include <iostream>
using namespace std;

#define LL long long

const int maxn = 100005;

LL c1[maxn], c2[maxn], sum[maxn];
int A[maxn], n;

inline int lowbit(int i) { return i & (-i); }

LL getsum(LL a[], int x) {
    LL ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += a[i];
    return ans;
}

void add(LL a[], int x, LL d) {
    for (int i = x; i <= n; i += lowbit(i))
        a[i] += d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    LL ans;
    int q, s, t, d;
    char ch;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + A[i];
    while (q--) {
        cin >> ch;
        if (ch == 'Q') {
            cin >> s >> t;
            ans = sum[t] - sum[s - 1];
            ans += (t + 1) * getsum(c1, t) - getsum(c2, t);
            ans -= s * getsum(c1, s - 1) - getsum(c2, s - 1);
            cout << ans << endl;
        } else {
            cin >> s >> t >> d;
            add(c1, s, d);
            add(c1, t + 1, -d);
            add(c2, s, d * s);
            add(c2, t + 1, -d * (t + 1));
        }
    }
    return 0;
}