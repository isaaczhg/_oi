#include <iostream>
using namespace std;

int a[2000005], q[2000005] = {0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, l = 1, r = 1, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = n + 1; i <= 2 * n; i++)
        a[i] = a[i - n];
    q[1] = 1;
    for (int i = 2; i <= 2 * n; i++) {
        while (l <= r && q[l] < i - n / 2)
            l++; //单调队列维护j
        ans = max(ans, a[i] + a[q[l]] + i - q[l]);
        while (l < r && a[i] - i >= a[q[r]] - q[r])
            r--;
        q[++r] = i;
    }
    cout << ans << "\n";
}