#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

struct tree {
    int a, b, h;
} a[80000 * 4 + 1], c[80000 * 4 + 1];
int b[80000 * 4 + 1];
long long ans;

bool cmp(const tree &a, const tree &b) { return a.h < b.h; }
void build(int v, int l, int r) {
    a[v].a = l;
    a[v].b = r;
    a[v].h = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build((v << 1) + 1, mid + 1, r);
}
void insert(int v, int l, int r, int x) {
    if (l > a[v].b || r < a[v].a)
        return;
    if (l <= a[v].a && r >= a[v].b) {
        a[v].h = x;
        return;
    }
    if (a[v].h > 0) {
        a[v << 1].h = a[(v << 1) + 1].h = a[v].h;
        a[v].h = -1;
    } //标记下传
    insert(v << 1, l, r, x);
    insert((v << 1) + 1, l, r, x);
    if (a[v << 1].h == a[(v << 1) + 1].h)
        a[v].h = a[v << 1].h; //标记上传,合并
}
void cal(int v) {
    if (a[v].h > 0) {
        ans += a[v].h * (long long)(b[a[v].b + 1] - b[a[v].a]);
        return;
    }
    if (a[v].a == a[v].b)
        return;
    cal(v << 1);
    cal((v << 1) + 1);
}
int main() {
    int n, tot;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &c[i].a, &c[i].b, &c[i].h);
        b[i] = c[i].a;
        b[i + n] = c[i].b;
    }
    sort(b + 1, b + (n << 1) + 1);
    tot = unique(b + 1, b + (n << 1) + 1) - b - 1;
    build(1, 1, tot);
    for (int i = 1; i <= n; i++) {
        c[i].a = lower_bound(b + 1, b + tot + 1, c[i].a) - b;
        c[i].b = lower_bound(b + 1, b + tot + 1, c[i].b) - b;
    } //离散化
    sort(c + 1, c + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        insert(1, c[i].a, c[i].b - 1, c[i].h); //记住转点
    cal(1);
    printf("%lld", ans);
    return 0;
}