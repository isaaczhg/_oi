#include <iostream>
#include <cstdio>
using namespace std;

int n, m, tot, maxx, ans;
int a[100005];

void solve(int x) {
    int s = 0;
    ans = 0;
    for (int i = 1; i <= n; i++) {
        s += a[i];
        if (s > x) {
            ans++;
            s = a[i];
        }
    }
}

int main() {
    int l, r, mid, Ans;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        tot += a[i];
        maxx = max(maxx, a[i]);
    }
    l  = maxx, r = tot;
    while (l <= r) {
        mid = (l + r) >> 1;
        solve(mid);
        if (ans + 1 <= m) {
            Ans = mid;
            r = mid - 1;
        }
        else 
            l = mid + 1;
    }
    printf("%d", Ans);
    return 0; 
}