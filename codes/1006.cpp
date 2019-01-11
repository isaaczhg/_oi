#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
struct node {
    int x, y, v;
} a[30005];
bool cmp(const node &a, const node &b) { return a.y < b.y; }
int main() {
    int f[30005] = {0}, n, maxx = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].v);
        maxx = max(maxx, a[i].y);
    }
    sort(a + 1, a + n + 1, cmp);
    int i = 1;
    for (int j = 1; j <= maxx; j++) {
        f[j] = f[j - 1];
        while (a[i].y == j) {
            f[j] = max(f[j], f[a[i].x] + a[i].v);
            i++;
        }
    }
    printf("%d", f[maxx]);
}