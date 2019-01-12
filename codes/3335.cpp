#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn = 100005;
const long double inf = 1e200;

struct point {
    long double x, y;
} p[Maxn];
struct line {
    point s, t;
    long double ang;
    int id;
    void init(point a, point b, int th) {
        s = a;
        t = b;
        id = th;
        ang = atan2(t.y - s.y, t.x - s.x);
    }
} l[Maxn * 2], a[Maxn * 2];
int n, m, h, t;
int q[Maxn * 2];

long double cross(point p1, point p2, point p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p1.y - p3.y) * (p2.x - p3.x);
}

bool cmp(line a, line b) {
    if (a.ang == b.ang)
        return cross(b.t, a.t, a.s) < 0;
    return a.ang < b.ang;
}

void get(int x, int y, point &p) {
    long double c1 = cross(a[x].s, a[y].t, a[y].s);
    long double c2 = cross(a[y].t, a[x].t, a[y].s);
    p.x = (a[x].s.x * c2 + a[x].t.x * c1) / (c1 + c2);
    p.y = (a[x].s.y * c2 + a[x].t.y * c1) / (c1 + c2);
}

bool judge(int now, int x, int y) {
    point p;
    get(x, y, p);
    return cross(a[now].t, p, a[now].s) < 0;
}

void half_plane(int x) {
    int cnt = 0;
    for (int i = 1; i <= m; i++)
        if (l[i].id <= x) {
            if (l[i].ang != a[cnt].ang)
                cnt++;
            a[cnt] = l[i];
        }
    h = 1;
    t = 0;
    q[++t] = 1;
    q[++t] = 2;
    for (int i = 3; i <= cnt; i++) {
        while (h < t && judge(i, q[t], q[t - 1]))
            t--;
        while (h < t && judge(i, q[h], q[h + 1]))
            h++;
        q[++t] = i;
    }
    while (h < t && judge(q[h], q[t], q[t - 1]))
        t--;
    while (h < t && judge(q[t], q[h], q[h + 1]))
        h++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long double x, y1, y2;
    int st, ed, mid, ans;
    l[++m].init((point){-inf, -inf}, (point){inf, -inf}, 0);
    l[++m].init((point){inf, -inf}, (point){inf, inf}, 0);
    l[++m].init((point){inf, inf}, (point){-inf, inf}, 0);
    l[++m].init((point){-inf, inf}, (point){-inf, -inf}, 0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y1 >> y2;
        l[++m].init((point){-1, y1 / x + x}, (point){1, y1 / x - x}, i);
        l[++m].init((point){1, y2 / x - x}, (point){-1, y2 / x + x}, i);
    }
    sort(l + 1, l + 1 + m, cmp);
    st = 1, ed = n;
    while (st <= ed) {
        mid = (st + ed) >> 1;
        half_plane(mid);
        if (t - h >= 2)
            st = mid + 1, ans = mid;
        else
            ed = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
