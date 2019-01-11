#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct point {
    double x, y;
} a[1005], b[1005];
int t, n, num;

void read() {
    cin >> t >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
}

double cross(point u, point v, point w) {
    return ((u.x - w.x) * (v.y - w.y) - (u.y - w.y) * (v.x - w.x));
}

void addcross(point u, point v, point w, point x) {
    double c1 = cross(x, v, u), c2 = cross(w, v, u);
    num++;
    b[num].x = (c1 * w.x - c2 * x.x) / (c1 - c2);
    b[num].y = (c1 * w.y - c2 * x.y) / (c1 - c2);
}

void cut(point u, point v) {
    num = 0;
    a[n + 1] = a[1];
    for (int i = 2; i <= n + 1; i++)
        if (cross(a[i - 1], v, u) <= 0) {
            b[++num] = a[i - 1];
            if (cross(a[i], v, u) > 0)
                addcross(a[i - 1], a[i], u, v);
        } else if (cross(a[i], v, u) < 0)
            addcross(a[i - 1], a[i], u, v);
    for (int i = 1; i <= num; i++)
        a[i] = b[i];
    n = num;
}

void half_plane() {
    int m;
    point u, v, w;
    for (int j = 2; j <= t; j++) {
        cin >> m;
        cin >> u.x >> u.y;
        w = u;
        for (int i = 2; i <= m; i++) {
            cin >> v.x >> v.y;
            cut(u, v);
            u = v;
        }
        cut(u, w);
    }
}
void area() {
    double ans = 0;
    a[n + 1] = a[1];
    for (int i = 1; i <= n; i++)
        ans += a[i].x * a[i + 1].y - a[i].y * a[i + 1].x;
    cout << fixed << setprecision(3) << fabs(ans) / 2 << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL)l
    read();
    half_plane();
    area();
    return 0;
}