#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 105;
int c[maxn][maxn][maxn], n;
int lowbit(int x) { return x & (-x); }
void add(int x, int y, int z) {
    for (int i = x; i < maxn; i += lowbit(i))
        for (int j = y; j < maxn; j += lowbit(j))
            for (int k = z; k < maxn; k += lowbit(k))
                c[i][j][k]++;
}
int sum(int x, int y, int z) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            for (int k = z; k > 0; k -= lowbit(k))
                ans += c[i][j][k];
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x1, x2, y1, y2, z1, z2, m, t;
    while (cin >> n >> m) {
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= m; i++) {
            cin >> t;
            if (t) {
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                add(x1, y1, z1);
                add(x2 + 1, y1, z1);
                add(x1, y2 + 1, z1);
                add(x1, y1, z2 + 1);
                add(x2 + 1, y2 + 1, z1);
                add(x2 + 1, y1, z2 + 1);
                add(x1, y2 + 1, z2 + 1);
                add(x2 + 1, y2 + 1, z2 + 1);
            } else {
                cin >> x1 >> y1 >> z1;
                cout << sum(x1, y1, z1) % 2 << "\n";
            }
        }
    }
    return 0;
}