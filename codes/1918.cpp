#include <iostream>
using namespace std;

struct point{
    int x, y;
} a[105];
int n, ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    a[n + 1] = a[1];
    for (int i = 1; i <= n; i++)
        ans += a[i].x * a[i + 1].y - a[i + 1].x * a[i].y;
    cout << (ans >> 1) << "\n";
    return 0;
}