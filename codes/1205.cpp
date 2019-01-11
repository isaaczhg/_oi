#include <iostream>
#include <cstdio>
using namespace std;

struct tree
{
    int l, r, c;
} a[200005 * 4 + 1];
int sum, h[200005 * 4 + 1], ans = 0, l, r, n, Delta;
void build(int v, int l, int r)
{
    a[v].l = l;
    a[v].r = r;
    a[v].c = 0;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(v << 1, l, mid);
    build((v << 1) + 1, mid + 1, r);
}
void push_down(int v)
{
    if (a[v].c >= 0)
    {
        a[v << 1].c = a[(v << 1) + 1].c = a[v].c;
        a[v].c = -1;
    }
}
void add(int v, int l, int r, int col)
{
    if (r < a[v].l || l > a[v].r)
        return;
    if (l <= a[v].l && r >= a[v].r)
    {
        a[v].c = col;
        return;
    }
    push_down(v);
    add(v << 1, l, r, col);
    add((v << 1) + 1, l, r, col);
}
void ask(int v, int l, int r)
{
    if (r < a[v].l || l > a[v].r)
        return;
    if (a[v].c == 0)
        return;
    if (a[v].c > 0)
    {
        h[a[v].c] = 1;
        return;
    }
    ask(v << 1, l, r);
    ask((v << 1) + 1, l, r);
}
int main()
{
    scanf("%d", &l);
    Delta = l - 1;
    l -= Delta;
    scanf("%d", &r);
    r = r - Delta - 1;
    build(1, l, r);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = l - Delta;
        r = r - Delta;
        if (l > r)
            continue;
        add(1, l, r - 1, i);
    }
    ask(1, l, r);
    for (int i = 1; i <= n; i++)
        if (h[i])
            ans++;
    printf("%d\n", ans);
    return 0;
}