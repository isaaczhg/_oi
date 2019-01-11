#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

const int Maxn = 30005;
struct point {
    double x, y;
} a[Maxn];
int stack[Maxn], p[Maxn * 2];
int n;
double maxn;

bool cmp(const point &u, const point &v) { return (u.y < v.y) || (u.y == v.y && u.x < v.x); }

double cross(point p1, point p2, point p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

void graham_scan() {
    int top = 0;
    stack[++top] = 1;
    stack[++top] = 2;
    for (int i = 3; i <= n; i++) {
        while (top > 1 && cross(a[stack[top]], a[i], a[stack[top - 1]]) <= 0)
            top--;
        stack[++top] = i;
    }
    for (int i = 1; i <= top; i++)
        p[++p[0]] = stack[i];
    top = 0;
    stack[++top] = n;
    stack[++top] = n - 1;
    for (int i = n - 2; i > 0; i--) {
        while (top > 1 && cross(a[stack[top]], a[i], a[stack[top - 1]]) <= 0)
            top--;
        stack[++top] = i;
    }
    for (int i = 2; i < top; i++)
        p[++p[0]] = stack[i];
}

double dis(point p1, point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void solve() {
    for (int i = 1; i < p[0]; i++)
        for (int j = i + 1; j <= p[0]; j++)
            maxn = (maxn < dis(a[p[i]], a[p[j]])) ? dis(a[p[i]], a[p[j]]) : maxn;
    cout << fixed << setprecision(2) << sqrt((double)maxn) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while(cin >> n) {
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++)
            cin >> a[i].x >> a[i].y;
        sort(a + 1, a + n + 1, cmp);
        graham_scan();
        solve();
    }
    return 0;
}
