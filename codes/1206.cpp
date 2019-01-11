#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

struct tree {
    int a, b, c, sum, acolor, bcolor;
    // sum表示标记总数 acolor表示左端点颜色 bcolor表示右端点颜色
} a[200000 * 4 + 1];
int xc, n;

void build(int v, int l, int r, int color) {
    a[v].a = l;
    a[v].b = r;
    a[v].acolor = a[v].bcolor = a[v].c = color;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(v << 1, l, mid, color);
    build((v << 1) + 1, mid + 1, r, color);
}
void pushdown(int v) {
    if (a[v].c >= 0) {
        a[v << 1].c = a[v << 1].acolor = a[v << 1].bcolor = a[(v << 1) + 1].c =
            a[(v << 1) + 1].acolor = a[(v << 1) + 1].bcolor = a[v].c;
        a[v << 1].sum = a[(v << 1) + 1].sum = 1;
        a[v].c = -1;
    }
}
void pushup(int v) {
    a[v].sum = a[v << 1].sum + a[(v << 1) + 1].sum;
    a[v].acolor = a[v << 1].acolor;
    a[v].bcolor = a[(v << 1) + 1].bcolor;
    if (a[v << 1].bcolor == a[(v << 1) + 1].acolor)
        a[v].sum--;
}
void add(int v, int l, int r, int color) {
    if (r < a[v].a || l > a[v].b)
        return;
    if (l <= a[v].a && r >= a[v].b) {
        a[v].acolor = a[v].bcolor = a[v].c = color;
        a[v].sum = 1;
        return;
    }
    pushdown(v);
    add(v << 1, l, r, color);
    add((v << 1) + 1, l, r, color);
    pushup(v);
}
int main() {
    int l, r, color;
    scanf("%d%d", &xc, &n);
    build(1, 1, 200001, xc);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &l, &r, &color);
        l += 100001;
        r += 100001;
        add(1, l, r - 1, color);
    }
    printf("%d\n", a[1].sum);
    return 0;
}