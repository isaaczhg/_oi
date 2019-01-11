#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#define LL long long
using namespace std;

const int Size = 50005;

struct point {
    int d[3], maxx[3], minn[3], l, r;
} a[Size << 1];
LL ansmax, ansmin;
int n, m, k, root, D;
int p[Size];

bool cmp(const point &x, const point &y) { return x.d[D] < y.d[D]; }
template <typename T> void max(T &x, const T y) { if (x < y) x = y; }
template <typename T> void min(T &x, const T y) { if (x > y) x = y; }
void pushup(int x) {
    int L = a[x].l, R = a[x].r;
    for (int i = 0; i < 2; i++) {
        if (L) {
            max(a[x].maxx[i], a[L].maxx[i]);
            min(a[x].minn[i], a[L].minn[i]);
        }
        if (R) {
            max(a[x].maxx[i], a[R].maxx[i]);
            min(a[x].minn[i], a[R].minn[i]);
        }
    }
}

void build(int &rt, int l, int r, int d) {
    int mid = (l + r) >> 1;
    D = d, rt = mid;
    nth_element(a + l, a + mid, a + r + 1, cmp);
    for (int i = 0; i < 2; i++)
        a[rt].maxx[i] = a[rt].minn[i] = a[rt].d[i];
    if (l < mid)
        build(a[rt].l, l, mid - 1, d ^ 1);
    if (r > mid)
        build(a[rt].r, mid + 1, r, d ^ 1);
    pushup(rt);
}

void askmax(int &maxx, int x, int y) {
    maxx = 0;
    for (int i = 0; i < 2; i++) 
        maxx += max(abs(a[x].minn[i] - a[y].d[i]), abs(a[x].maxx[i] - a[y].d[i]));
}

void askmin(int &minn, int x, int y) {
    minn = 0;
    for (int i = 0; i < 2; i++) {
        if (a[y].d[i] < a[x].minn[i])
            minn += a[x].minn[i] - a[y].d[i];
        if (a[y].d[i] > a[x].maxx[i])
            minn += a[y].d[i] - a[x].maxx[i];
    }
}

void query_max(int x, int d, int y) {
    LL dist = (LL)(abs(a[x].d[0] - a[y].d[0]) + abs(a[x].d[1] - a[y].d[1]));
    int dl = -1, dr = -1;
    if (y != x)
        max(ansmax, dist);
    if (a[x].l)
        askmax(dl, a[x].l, y);
    if (a[x].r)
        askmax(dr, a[x].r, y);     
    if (dl > dr) {
        if (dl > ansmax)
            query_max(a[x].l, d ^ 1, y);
        if (dr > ansmax)
            query_max(a[x].r, d ^ 1, y); 
    }
    else {
        if (dr > ansmax)
            query_max(a[x].r, d ^ 1, y);
        if (dl > ansmax)
            query_max(a[x].l ,d ^ 1, y);
    }  
}

void query_min(int x, int d, int y) {
    LL dist = abs(a[x].d[0] - a[y].d[0]) + abs(a[x].d[1] - a[y].d[1]);
    int dl = 0x7fffffff, dr = 0x7fffffff;
    if (y != x)
        min(ansmin, dist);
    if (a[x].l)
        askmin(dl, a[x].l, y);
    if (a[x].r)
        askmin(dr, a[x].r, y);     
    if (dl < dr) {
        if (dl < ansmin)
            query_min(a[x].l, d ^ 1, y);
        if (dr < ansmin)
            query_min(a[x].r, d ^ 1, y); 
    }
    else {
        if (dr < ansmin)
            query_min(a[x].r, d ^ 1, y);
        if (dl < ansmin)
            query_min(a[x].l ,d ^ 1, y);
    }  
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    LL ans = 0x7fffffff;
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> a[i].d[0] >> a[i].d[1];
    build(root, 1, n, 0);
    for (int i = 1; i <= n; i++) {
        ansmax = -1, ansmin = 0x7fffffff;
        query_max(root, 0, i);
        query_min(root, 0, i);
        min(ans, ansmax - ansmin);
    }
    cout << ans << "\n";
    return 0;
}