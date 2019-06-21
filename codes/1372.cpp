#include <iostream>
#include <cstdio>
using namespace std;

int n, m, ans;
int map[1005][1005], l[1005][1005], r[1005][1005], h[1005][1005];
char ch;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) {
            cin >> ch;
            if (ch == 'R')
                map[i][j] = 0;
            else 
                map[i][j] = 1;
            l[i][j] = r[i][j] = j;
            h[i][j] = 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 2; j <= m; j++) 
            if (map[i][j] && map[i][j - 1])
                l[i][j] = l[i][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = m - 1; j >= 1; j--)
            if (map[i][j] && map[i][j + 1])
                r[i][j] = r[i][j + 1];
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (map[i][j] && map[i - 1][j]) {
                h[i][j] = h[i - 1][j] + 1;
                l[i][j] = max(l[i][j], l[i - 1][j]);
                r[i][j] = min(r[i][j], r[i - 1][j]);
            }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans = max(ans, (r[i][j] - l[i][j] + 1) * h[i][j]);
        printf("%d\n", ans * 3);
    return 0;
}