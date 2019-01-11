#include <cstdio>
#include <algorithm>
using namespace std;

const int Maxn = 2005;
struct point {
    double x, y;
} a[Maxn];
int stack[Maxn * 2], q[Maxn * 3] = {0}, n, top;

bool cmp(const point &u, const point &v) { return (u.y < v.y) || (u.y == v.y && u.x < v.x); }

double maxn = -1e8;

void read() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &a[i].x, &a[i].y);
}

double cross(point p1, point p2, point p0) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

void graham_scan() {
    int i;
    top = 2;
    stack[1] = 1;
    stack[2] = 2;
    for (i = 3; i <= n; i++) {
        while (cross(a[i], a[stack[top]], a[stack[top - 1]]) >= 0 && top > 1)
            top--;
        top++;
        stack[top] = i;
    }
    for (i = 1; i <= top; i++)
        q[++q[0]] = stack[i];
    top = 2;
    stack[1] = n;
    stack[2] = n - 1;
    for (i = n - 2; i > 0; i--) {
        while (cross(a[i], a[stack[top]], a[stack[top - 1]]) >= 0 && top > 1)
            top--;
        top++;
        stack[top] = i;
    }
    if (q[q[0]] == stack[1])
        i = 2;
    else
        i = 1;
    for (; i < top; i++)
        q[++q[0]] = stack[i];
}

void solve() {
    int n1, n2, n3, n4;
    double area, s1, s2;
    for (int i = 1; i <= q[0]; i++)
        q[q[0] + i] = q[i];
    for (int k = 1; k <= q[0] - 2; k++) {
        n1 = k;
        n2 = k + 1;
        n4 = k + 3;
        for (int i = k + 2; i <= q[0] - (k == 1); i++) {
            n3 = i;
            s1 = cross(a[q[n2]], a[q[n3]], a[q[n1]]);
            s2 = cross(a[q[n3]], a[q[n4]], a[q[n1]]);
            while (n2 + 1 < n3) {
                area = cross(a[q[n2 + 1]], a[q[n3]], a[q[n1]]);
                if (area > s1) {
                    s1 = area;
                    n2++;
                } else
                    break;
            }
            while (n4 + 1 < n1 + q[0]) {
                area = cross(a[q[n3]], a[q[n4 + 1]], a[q[n1]]);
                if (area > s2) {
                    s2 = area;
                    n4++;
                } else
                    break;
            }
            if (s1 + s2 > maxn)
                maxn = s1 + s2;
        }
    }
}

int main() {
    read();
    sort(a + 1, a + n + 1, cmp);
    graham_scan();
    solve();
    printf("%.3lf\n", maxn / 2);
}
