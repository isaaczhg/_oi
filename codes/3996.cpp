#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#define LL long long
using namespace std;

const int k = 2;
const int Maxn = 100005;
int n, d, m;
LL ans[25];
struct point {
    int x[2], minx[2], maxx[2], id;
} p[Maxn], a[Maxn << 1], now, bj[25];

bool operator <(const point &a, const point &b) {
    return a.x[d] < b.x[d] || (a.x[d] == b.x[d] && a.id > b.id);
}

void pushup(int x, int y) {
    a[x].minx[0] = min(a[x].minx[0], a[y].minx[0]);
    a[x].maxx[0] = max(a[x].maxx[0], a[y].maxx[0]);
    a[x].minx[1] = min(a[x].minx[1], a[y].minx[1]);
    a[x].maxx[1] = max(a[x].maxx[1], a[y].maxx[1]);
}

void build(int x, int l, int r, int dep) {
    d = dep % k;
    int mid = (l + r) >> 1;
    nth_element(p + l, p + mid, p + r + 1);
    a[x] = p[mid];
    if (l == r)
        return;
    if (l <= mid - 1) {
        build(x << 1, l, mid - 1, dep + 1);
        pushup(x, x << 1);
    }
    if (r >= mid + 1) {
        build(x << 1 ^ 1, mid + 1, r, dep + 1);
        pushup(x, x << 1 ^ 1);
    }
}

LL square(int x) { return (LL)x * x; }

LL dis(point a, point b) {
    return square(a.x[0] - b.x[0]) + square(a.x[1] - b.x[1]);
}

void rean(point a) {
    LL tmp = dis(a, now);
    for (int i = 1; i <= m; i++)
        if (tmp > ans[i] || (tmp == ans[i] && a.id < bj[i].id)) {
            for (int j = m; j >= i + 1; j--) {
                ans[j] = ans[j - 1];
                bj[j] = bj[j - 1];
            }
            ans[i] = tmp;
            bj[i] = a;
            break;
        }
}

void query(int x, int l, int r, int dep) {
    d = dep % k;
    LL x0 =
        max(square(now.x[0] - a[x].maxx[0]), square(now.x[0] - a[x].minx[0]));
    LL x1 =
        max(square(now.x[1] - a[x].maxx[1]), square(now.x[1] - a[x].minx[1]));
    if (x0 + x1 < ans[m])
        return;
    rean(a[x]);
    int mid = (l + r) >> 1;
    if (now < a[x]) {
        if (r >= mid + 1)
            query(x << 1 ^ 1, mid + 1, r, dep + 1);
        if (l <= mid - 1)
            query(x << 1, l, mid - 1, dep + 1);
    } else {
        if (l <= mid - 1)
            query(x << 1, l, mid - 1, dep + 1);
        if (r >= mid + 1)
            query(x << 1 ^ 1, mid + 1, r, dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < k; j++) {
            cin >> p[i].x[j];
            p[i].id = i;
            p[i].maxx[j] = p[i].minx[j] = p[i].x[j];
        }
    build(1, 1, n, 0);
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> now.x[0] >> now.x[1];
        cin >> m;
        for (int i = 1; i <= m; i++)
            ans[i] = -1;
        query(1, 1, n, 0);
        cout << bj[m].id << "\n";
    }
    return 0;
}