#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
struct node {
    int x, y;
} a[500005];
int b[500005];
bool cmp(const node &x, const node &y) { return x.x < y.x; }
int main() {
    int n, l, r, mid, len = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1, cmp);
    b[1] = a[1].y;
    // for(int i=1;i<=n;i++)cout<<a[i].x<<" "<<a[i].y<<endl;
    for (int i = 2; i <= n; i++) {
        l = 1;
        r = len;
        if (b[len] < a[i].y) {
            len++;
            b[len] = a[i].y;
            continue;
        }
        while (l <= r) {
            mid = (l + r) >> 1;
            if (b[mid] < a[i].y)
                l = mid + 1;
            else
                r = mid - 1;
        }
        b[l] = a[i].y;
    }
    printf("%d", len);
}