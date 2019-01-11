#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct point {
    int x, y;
} a[105];
int n;
int b[105], q[105];

bool cmp(const point &u, const point &v) { return (u.y < v.y) || (u.y == v.y && u.x < v.x); }

void read() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
}

double dis(point x, point y) {
    return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}

int cross(point p1, point p2, point p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

void graham_scan() {
    int top;
    q[1] = 1;
    q[2] = 2;
    top = 2;
    for (int i = 3; i <= n; i++) {
        while (top > 1 && cross(a[q[top]], a[i], a[q[top - 1]]) <= 0)
            top--;
        q[++top] = i;
    }
    for (int i = 1; i <= top; i++)
        b[++b[0]] = q[i];
    q[1] = n;
    q[2] = n - 1;
    top = 2;
    for (int i = n - 2; i >= 1; i--) {
        while (top > 1 && cross(a[q[top]], a[i], a[q[top - 1]]) <= 0)
            top--;
        q[++top] = i;
    }
    for (int i = 2; i <= top - 1; i++)
        b[++b[0]] = q[i];
}

void area() {
    double s = 0, l = 0;
    b[b[0] + 1] = b[1];
    for (int i = 1; i <= b[0]; i++) {
        s += cross(a[b[i]], a[b[i + 1]], a[0]);
        l += dis(a[b[i]], a[b[i + 1]]);
    }
    s = abs(s) / 2;
    if (s == 0)
        l = l / 2;
    cout << fixed << setprecision(2) << l << "\n" << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    read();
    sort(a + 1, a + n + 1, cmp);
    if (n == 2)
        cout << fixed << setprecision(2) << dis(a[1], a[2]) << "\n" << 0.00;
    else {
        graham_scan();
        area();
    }
    return 0;
}