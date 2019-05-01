#include <cstdio>
#include <iostream>
using namespace std;
int n, p, ans = 305;
int map[305][305], a[305][305];

void maketree(int x) {
    for (int i = 1; i <= n; i++)
        if (map[x][i]) {
            a[x][++a[x][0]] = i;
            map[x][i] = 0;
            map[i][x] = 0;
            maketree(i);
        }
}

void dfs(int root, int s) {
    int k, x, x1, x2, t;
    if (s + a[root][0] - 1 >= ans)
        return; //最优性剪枝
    if (a[root][0] <= 1) {
        ans = min(ans, s);
        return;
    }
    for (int i = 1; i <= a[root][0]; i++) {
        if (i == 1)
            x1 = 2;
        else
            x1 = 1;
        x = a[root][x1];
        t = a[x][0];
        for (int j = 1; j <= a[root][0]; j++)
            if (j != i && j != x1) {
                x2 = a[root][j];
                for (k = 1; k <= a[x2][0]; k++)
                    a[x][++a[x][0]] = a[x2][k];
            }
        dfs(x, s + a[root][0] - 1);
        a[x][0] = t;
    }
}

int main() {
	//freopen("epidemic.in", "r", stdin);
	//freopen("epidemic.out", "w", stdout);
    int x, y;
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= p; i++) {
        cin >> x >> y;
        map[x][y] = 1;
        map[y][x] = 1;
    }
    maketree(1);
    dfs(1, 1);
    printf("%d\n", ans);
    return 0;
}
