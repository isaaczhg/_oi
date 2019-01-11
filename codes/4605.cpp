#include <iostream>
#include <queue>
#include <algorithm>
#define ll long long
using namespace std;

struct point {
    int d[2], maxx[2], minn[2], l, r;
} a[100005];
int n, k, root, p[2], D;
priority_queue<ll, vector<ll>, greater<ll>> q;

inline void max(int &x, const int &y) { if (x < y) x = y; }
inline void min(int &x, const int &y) { if (x > y) x = y; }
inline ll sqr(const int &x) { return (ll)x * x; }

bool cmp(const point &x, const point &y) { return x.d[D] < y.d[D]; }

void pushup(int x) {
    int l = a[x].l, r = a[x].r;
    for (int i = 0; i < 2; i++) {
        if (l) {
            max(a[x].maxx[i], a[l].maxx[i]);
            min(a[x].minn[i], a[l].minn[i]);
        }
        if (r) {
            max(a[x].maxx[i], a[r].maxx[i]);
            min(a[x].minn[i], a[r].minn[i]);
        }
    }
}

void build(int &x, int l, int r, int now) {
    int mid = (l + r) >> 1;
    D = now;
    x = mid;
    nth_element(a + l, a + mid, a + r + 1, cmp);
    for (int i = 0; i < 2; i++)
        a[x].maxx[i] = a[x].minn[i] = a[x].d[i];
    if (l < mid)
        build(a[x].l, l, mid - 1, now ^ 1);
    if (r > mid)
        build(a[x].r, mid + 1, r, now ^ 1);
    pushup(x);
}

ll ask(int x) {
    if (!x)
        return 0;
    return max(sqr(a[x].minn[0] - p[0]), sqr(a[x].maxx[0] - p[0])) + max(sqr(a[x].minn[1] - p[1]), sqr(a[x].maxx[1] - p[1]));
}

void query(int x) {
    ll dist = sqr(a[x].d[0] - p[0]) + sqr(a[x].d[1] - p[1]);
    if (dist > q.top()) {
        q.pop();
        q.push(dist);
    }
    ll dl = ask(a[x].l), dr = ask(a[x].r);
    if (dl > dr) {
        if (dl > q.top())
            query(a[x].l);
        if (dr > q.top())
            query(a[x].r);
    } else {
        if (dr > q.top())
            query(a[x].r);
        if (dl > q.top())
            query(a[x].l);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i].d[0] >> a[i].d[1];
    build(root, 1, n, 0);
    for (int i = 1; i <= 2 * k; i++)
        q.push(0);
    for (int i = 1; i <= n; i++) {
        p[0] = a[i].d[0];
        p[1] = a[i].d[1];
        query(root);
    }
    cout << q.top() << "\n";
    return 0;
}
