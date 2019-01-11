#include <iostream>
using namespace std;

int n, x, now, s, l = 0, r = 0, ans = 0, son[1000005], q[1000005], rd[1000005] = {0}, bj[1000005] = {0}, a[1000005] = {0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> son[i];
        rd[son[i]]++;
    }
    for (int i = 1; i <= n; i++)
        if (!rd[i])
            q[++r] = i;
    while (l < r) {
        l++;
        x = q[l];
        bj[x] = 1;
        if (a[x])
            ans++;
        else
            a[son[x]] = 1;
        rd[son[x]]--;
        if (!rd[son[x]])
            q[++r] = son[x];
    }
    l = 0;
    r = 0;
    for (int i = 1; i <= n; i++)
        if (!bj[i] && a[i])
            q[++r] = i, bj[i] = 1;
    while (l < r) {
        l++;
        x = q[l];
        if (a[x])
            ans++;
        else
            a[son[x]] = 1;
        if (!bj[son[x]]) {
            q[++r] = son[x];
            bj[son[x]] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
        if (!bj[i]) {
            now = i;
            s = 0;
            while (now != i || !s) {
                bj[now] = 1;
                s++;
                now = son[now];
            }
            ans += s / 2;
        }
    cout << ans << "\n";
}