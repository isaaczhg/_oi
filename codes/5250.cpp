#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

const double eps = 1e-8;
const int Maxn = 20005;
struct point {
    double x, y;
} p[Maxn];
struct line {
    point a, b;
    double angle;
} l[Maxn];
int n, pn;
int dq[Maxn], top, bot;

int dblcmp(double k) {
    if (fabs(k) < eps)
        return 0;
    return k > 0 ? 1 : -1;
}

double multi(point p0, point p1, point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

bool cmp(const line &l1, const line &l2) {
    int d = dblcmp(l1.angle - l2.angle);
    if (!d)
        return dblcmp(multi(l1.a, l2.a, l2.b)) > 0;
    return d < 0;
}

void addline(line &l, double x1, double y1, double x2, double y2) {
    l.a.x = x1;
    l.a.y = y1;
    l.b.x = x2;
    l.b.y = y2;
    l.angle = atan2(y2 - y1, x2 - x1);
}

void get(line l1, line l2, point &p) {
    double a1 = l1.b.y - l1.a.y;
    double b1 = l1.a.x - l1.b.x;
    double c1 = (l1.b.x - l1.a.x) * l1.a.y - (l1.b.y - l1.a.y) * l1.a.x;
    double a2 = l2.b.y - l2.a.y;
    double b2 = l2.a.x - l2.b.x;
    double c2 = (l2.b.x - l2.a.x) * l2.a.y - (l2.b.y - l2.a.y) * l2.a.x;
    p.x = (c2 * b1 - c1 * b2) / (a1 * b2 - a2 * b1);
    p.y = (c1 * a2 - c2 * a1) / (a1 * b2 - a2 * b1);
}

bool judge(line l0, line l1, line l2) {
    point p;
    get(l1, l2, p);
    return dblcmp(multi(p, l0.a, l0.b)) < 0;
}

void half_plane() {
    int i, j;
    sort(l, l + n, cmp);
    for (i = 0, j = 0; i < n; i++)
        if (dblcmp(l[i].angle - l[j].angle) > 0)
            l[++j] = l[i];
    n = j + 1;
    dq[0] = 0;
    dq[1] = 1;
    top = 1;
    bot = 0;
    for (i = 2; i < n; i++) {
        while (top > bot && judge(l[i], l[dq[top]], l[dq[top - 1]]))
            top--;
        while (top > bot && judge(l[i], l[dq[bot]], l[dq[bot + 1]]))
            bot++;
        dq[++top] = i;
    }
    while (top > bot && judge(l[dq[bot]], l[dq[top]], l[dq[top - 1]]))
        top--;
    while (top > bot && judge(l[dq[top]], l[dq[bot]], l[dq[bot + 1]]))
        bot++;
    dq[++top] = dq[bot];
    for (pn = 0, i = bot; i < top; i++, pn++)
        get(l[dq[i + 1]], l[dq[i]], p[pn]);
}

double area() {
    if (pn < 3)
        return 0;
    double area = 0;
    for (int i = 1; i < pn - 1; i++)
        area += multi(p[0], p[i], p[i + 1]);
    if (area < 0)
        area = -area;
    return area / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    double x1, y1, x2, y2;
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            addline(l[i], x1, y1, x2, y2);
        }
        addline(l[n++], 0, 0, 10000, 0);
        addline(l[n++], 10000, 0, 10000, 10000);
        addline(l[n++], 10000, 10000, 0, 10000);
        addline(l[n++], 0, 10000, 0, 0);
        half_plane();
        cout << fixed << setprecision(1) << area() << "\n";
    }
    return 0;
}
