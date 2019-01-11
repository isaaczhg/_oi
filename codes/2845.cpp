#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int Maxn = 1000005;
const int inf = 0x7fffffff / 2;
const double eps = 1e-9;

struct node {
    double x, y, a, b, k, rate;
    int w, id;
    bool operator<(const node &a) const { return a.k < k; }
} p[Maxn], t[Maxn];
int n, top;
double s;
int st[Maxn];
double f[Maxn];

double getk(int a, int b) {
    if (b == 0)
        return -inf;
    if (fabs(p[a].x - p[b].x) < eps)
        return inf;
    return (p[b].y - p[a].y) / (p[b].x - p[a].x);
}

void cdq(int l, int r) {
    if (l == r) {
        f[l] = max(f[l], f[l - 1]);
        p[l].y = f[l] / (p[l].a * p[l].rate + p[l].b);
        p[l].x = p[l].rate * p[l].y;
        return;
    }
    int l1, l2, mid = (l + r) >> 1, j = 1;
    l1 = l;
    l2 = mid + 1;
    for (int i = l; i <= r; i++) {
        if (p[i].id <= mid)
            t[l1++] = p[i];
        else
            t[l2++] = p[i];
    }
    for (int i = l; i <= r; i++)
        p[i] = t[i];
    cdq(l, mid);
    top = 0;
    for (int i = l; i <= mid; i++) {
        while (top > 1 &&
               getk(st[top - 1], st[top]) < getk(st[top - 1], i) + eps)
            top--;
        st[++top] = i;
    }
    st[++top] = 0;
    for (int i = mid + 1; i <= r; i++) {
        while (j < top && getk(st[j], st[j + 1]) + eps > p[i].k)
            j++;
        f[p[i].id] = max(f[p[i].id], p[st[j]].x * p[i].a + p[st[j]].y * p[i].b);
    }
    cdq(mid + 1, r);
    l1 = l;
    l2 = mid + 1;
    for (int i = l; i <= r; i++) {
        if (((p[l1].x < p[l2].x ||
              (fabs(p[l1].x - p[l2].x) < eps && p[l1].y < p[l2].y)) ||
             l2 > r) &&
            l1 <= mid)
            t[i] = p[l1++];
        else
            t[i] = p[l2++];
    }
    for (int i = l; i <= r; i++)
        p[i] = t[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> f[0];
    for (int i = 1; i <= n; i++) {
        cin >> p[i].a >> p[i].b >> p[i].rate;
        p[i].k = -p[i].a / p[i].b;
        p[i].id = i;
    }
    sort(p + 1, p + 1 + n);
    cdq(1, n);
    cout << fixed << setprecision(3) << f[n] << "\n";
    return 0;
}