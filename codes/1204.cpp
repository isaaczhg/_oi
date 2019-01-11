#include <cstdio>
#include <iostream>
using namespace std;

struct tree
{
    int a, b, sum;
} a[200000 * 4 + 1];

void add(int v, int l, int r)
{
    if (l > a[v].b || r < a[v].a)
        return;
    if (l <= a[v].a && r >= a[v].b)
    {
        a[v].sum = a[v].b - a[v].a + 1;
        return;
    }
    if (a[v].sum == a[v].b - a[v].a + 1)
        return; //完全覆盖
    if (a[v << 1].sum < a[v << 1].b - a[v << 1].a + 1)
        add(v << 1, l, r);
    if (a[(v << 1) + 1].sum < a[(v << 1) + 1].b - a[(v << 1) + 1].a + 1)
        add((v << 1) + 1, l, r);
    a[v].sum = a[v << 1].sum + a[(v << 1) + 1].sum;
}
void build(int v, int l, int r)
{
    a[v].a = l;
    a[v].b = r;
    a[v].sum = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build((v << 1) + 1, mid + 1, r);
}
int main()
{
    int L, R, n, bl, br, d;
    scanf("%d%d%d", &L, &R, &n);
    d = -L;
    build(1, L + d, R + d - 1);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &bl, &br);
        add(1, bl + d, br + d - 1);
    }
    printf("%d\n", a[1].sum);
    return 0;
}