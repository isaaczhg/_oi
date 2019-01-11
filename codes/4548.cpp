#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn = 100005;

int n, k, cnt, top;
int c[Maxn << 1], ans[Maxn];
struct query {
    int a, b, c, sum, num;
    bool operator<(const query &A) const {
        return b == A.b ? c < A.c : b < A.b;
    }
    bool operator!=(const query &A) const {
        return a != A.a || b != A.b || c != A.c;
    }
} s[Maxn], q[Maxn];

bool cmp(const query &a, const query &b) {
    if (a.a == b.a && a.b == b.b)
        return a.c < b.c;
    if (a.a == b.a)
        return a.b < b.b;
    return a.a < b.a;
}

inline int lowbit(int x) { return x & (-x); }

void add(int x, int d) {
    for (int i = x; i <= k; i += lowbit(i))
        c[i] += d;
}

int Sum(int x) {
    int tmp = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        tmp += c[i];
    return tmp;
}

void cdq(int l, int r) {
    int mid = (l + r) >> 1;
    if (l == r)
        return;
    cdq(l, mid);
    cdq(mid + 1, r);
    sort(q + l, q + mid + 1);
    sort(q + mid + 1, q + r + 1);
    int tp1 = l;
    for (int i = mid + 1; i <= r; i++) {
        while (tp1 <= mid && q[tp1].b <= q[i].b)
            add(q[tp1].c, q[tp1].num), tp1++;
        q[i].sum += Sum(q[i].c);
    }
    for (int i = l; i < tp1; i++)
        add(q[i].c, -q[i].num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> s[i].a >> s[i].b >> s[i].c;
    sort(s + 1, s + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        cnt++;
        if (s[i] != s[i + 1]) {
            q[++top] = s[i];
            q[top].num = cnt;
            cnt = 0;
        }
    }
    cdq(1, top);
    for (int i = 1; i <= top; i++)
        ans[q[i].sum + q[i].num - 1] += q[i].num;
    for (int i = 0; i < n; i++)
        cout << ans[i] << "\n";
    return 0;
}