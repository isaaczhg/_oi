#include <algorithm>
#include <iostream>
using namespace std;
struct tyc {
    int id, c;
} a[200005];
int n, bj, ans, m, l[200005], r[200005];

bool cmp(tyc a, tyc b) { return (a.c == b.c) ? a.id < b.id : a.c < b.c; }

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].c);
        a[i].id = i;
    }
    sort(1 + a, 1 + a + n, cmp);
    a[0].c = -0x7fffffff / 2;
    for (int i = 1; i <= n; i++) {
        if (a[i].c != a[i - 1].c) {
            m++;
            l[m] = a[i].id;
            r[m] = a[i].id;
        }
        l[m] = min(l[m], a[i].id);
        r[m] = max(r[m], a[i].id);
    }
    bj = 1;
    for (int i = 1; i <= m; i++) {
        if (bj == 1 && r[i] >= l[i - 1])
            bj = 0;
        else if (bj == 0 && l[i] <= r[i - 1]) {
            bj = 1;
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
