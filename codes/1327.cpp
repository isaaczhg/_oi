#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
struct p {
    double x, y;
} a[60005], tmp[60005];
bool cmp1(const p &a, const p &b) { return a.x < b.x; }
bool cmp2(const p &a, const p &b) { return a.y < b.y; }
double dis(p a, p b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
double find(int l, int r) {
    int mid, tot;
    double minn, xit, t;
    if (l == r)
        return 1e20;
    if (l + 1 == r)
        return dis(a[l], a[r]);
    mid = (l + r) / 2;
    minn = find(l, mid);
    t = find(mid + 1, r);
    if (t < minn)
        minn = t;
    tot = 0;
    xit = (a[mid].x + a[mid + 1].x) / 2;
    for (int i = l; i <= r; i++)
        if (abs(a[i].x - xit) < minn) {
            tot++;
            tmp[tot].x = a[i].x;
            tmp[tot].y = a[i].y;
        }
    if (tot > 1)
        sort(tmp + 1, tmp + tot + 1, cmp2);
    for (int i = 1; i <= tot - 1; i++)
        for (int j = i + 1; j <= i + 6; j++) {
            if (j > tot)
                break;
            t = dis(tmp[i], tmp[j]);
            if (t < minn)
                minn = t;
        }
    return minn;
}
int n;
int main() {
	scanf("%d", &n);
    for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1, cmp1);
	printf("%.2lf\n", sqrt(find(1, n)));
    return 0;
}