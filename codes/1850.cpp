#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct point {
    double x, y;
} a[1005], b[1005], c[1005];
int m, n, num;

void read() {
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    for (int i = 1; i <= n; i++)
        c[i] = a[i];
    m = n;
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
        if (cross(a[i - 1], v, u) >= 0) {
            b[++num] = a[i - 1];
            if (cross(a[i], v, u) < 0)
                addcross(a[i - 1], a[i], u, v);
        } else if (cross(a[i], v, u) > 0)
            addcross(a[i - 1], a[i], u, v);
    for (int i = 1; i <= num; i++)
        a[i] = b[i];
    n = num;
}

void half_plane() {
    for (int i = 2; i <= m; i++)
        cut(c[i - 1], c[i]);
    cut(c[m], c[1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int sum = 0;
    cin >> n;
    while (n) {
        read();
        half_plane();
        cout << "Floor #" << ++sum << "\n";
        if (n)
            cout << "Surveillance is possible.\n\n";
        else
            cout << "Surveillance is impossible.\n\n";
        cin >> n;
    }
    return 0;
}
