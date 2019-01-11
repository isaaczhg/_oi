//极角排序
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct point {
    int x, y;
} a[105];
int n, t;
int b[105];
double s, l;

double dis(point x, point y) {
    return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}

int cross(point p1, point p2, point p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool cmp(const point &u, const point &v) {
    int tmp = cross(a[1], u, v);
    if (tmp > 0)
        return 1;
    else if (tmp == 0)
        return dis(a[1], u) < dis(a[1], v);
    else
        return 0;
}

void read() {
    int minx, miny, k;
    cin >> n;
    minx = 0x7fffffff >> 1;
    miny = 0x7fffffff >> 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
        if ((miny > a[i].y) || ((miny == a[i].y) && (minx > a[i].x))) {
            minx = a[i].x;
            miny = a[i].y;
            k = i;
        }
    }
    swap(a[1], a[k]);
}

void scan() {
    b[1] = 1;
    b[2] = 2;
    t = 2;
    for (int i = 3; i <= n; i++) {
        while (t > 1 && cross(a[b[t]], a[i], a[b[t - 1]]) <= 0)
            t--;
        b[++t] = i;
    }
}

void area() {
    b[++t] = b[1];
    s = 0;
    l = 0;
    for (int i = 2; i <= t; i++) {
        s += cross(a[b[i - 1]], a[b[i]], a[1]);
        l += dis(a[b[i]], a[b[i - 1]]);
    }
    s = abs(s) / 2;
    if (s == 0)
        l = l / 2;
    cout << fixed << setprecision(2) << l << "\n";
    cout << fixed << setprecision(2) << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    read();
    sort(a + 2, a + n + 1, cmp);
    scan();
    area();
}