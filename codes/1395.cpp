#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#define LL long long
using namespace std;

const int Size = 50005;

struct point {
    int d[6], maxx[6], minn[6], l, r;
} a[Size << 1];
priority_queue<pair<LL, int>> q;
int n, m, k, root, D, t;
int p[Size];

bool cmp(const point &x, const point &y) { return x.d[D] < y.d[D]; }

void pushup(int x) {
    int L = a[x].l, R = a[x].r;
    for (int i = 0; i < k; i++) {
        if (L) {
            a[x].maxx[i] = max(a[x].maxx[i], a[L].maxx[i]);
            a[x].minn[i] = min(a[x].minn[i], a[L].minn[i]);
        }
        if (R) {
            a[x].maxx[i] = max(a[x].maxx[i], a[R].maxx[i]);
            a[x].minn[i] = min(a[x].minn[i], a[R].minn[i]);
        }
    }
}

void build(int &rt, int l, int r, int d) {
    int mid = (l + r) >> 1;
    D = d, rt = mid;
    nth_element(a + l, a + mid, a + r + 1, cmp);
    for (int i = 0; i < k; i++)
        a[rt].maxx[i] = a[rt].minn[i] = a[rt].d[i];
    if (l < mid)
        build(a[rt].l, l, mid - 1, (d + 1) % k);
    if (r > mid)
        build(a[rt].r, mid + 1, r, (d + 1) % k);
    pushup(rt);
}

LL dis(int x) {
    LL ans = 0;
    for (int i = 0; i < k; i++)
        ans += (LL)(p[i] - a[x].d[i]) * (p[i] - a[x].d[i]);
    return ans;
}

LL guess(int x) {
    LL ans = 0;
    for (int i = 0; i < k; i++) {
        if (p[i] > a[x].maxx[i])
            ans += (LL)(p[i] - a[x].maxx[i]) * (p[i] - a[x].maxx[i]);
        if (p[i] < a[x].minn[i])
            ans += (LL)(p[i] - a[x].minn[i]) * (p[i] - a[x].minn[i]);
    }
    return ans;
}

void query(int x) {
    if (!x)
        return;
    long long dist = dis(x), dl = guess(a[x].l), dr = guess(a[x].r);
    if (dist < q.top().first) {
        q.pop();
        q.push(make_pair(dist, x));
    }
    if (dl < dr) {
        if (dl < q.top().first)
            query(a[x].l);
        if (dr < q.top().first)
            query(a[x].r);
    } else {
        if (dr < q.top().first)
            query(a[x].r);
        if (dl < q.top().first)
            query(a[x].l);
    }
}

void print() {
    int x;
    while (!q.empty()) {
        x = q.top().second;
        q.pop();
        print();
        for (int i = 0; i < k; i++)
            cout << a[x].d[i] << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n >> k) {
        memset(a, 0, sizeof(a));
        while (!q.empty())
            q.pop();
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < k; j++)
                cin >> a[i].d[j];
        build(root, 1, n, 0);
        cin >> t;
        for (int i = 1; i <= t; i++) {
            for (int j = 0; j < k; j++)
                cin >> p[j];
            cin >> m;
            for (int j = 1; j <= m; j++)
                q.push(make_pair(0x7fffffff, 0));
            query(root);
            cout << "the closest " << m << " points are:"
                 << "\n";
            print();
        }
    }
    return 0;
}