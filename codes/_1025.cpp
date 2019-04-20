#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct edge {
    int to, nxt, v;
} e[705];
int f[305][305][2], Size[305], h[305];
int n, m, k, cnt;

void addedge(int x, int y, int z) {
    e[++cnt].to = y;
    e[cnt].v = z;
    e[cnt].nxt = h[x];
    h[x] = cnt;
}

void treedp(int x, int prt) {
    int t;
    Size[x] = 1;
    f[x][1][1] = f[x][0][0] = 0;
    for (int i = h[x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if (y == prt)
            continue;
        treedp(y, x);
        Size[x] += Size[y];
        if (m == 2)
            t = e[i].v;
        else 
            t = 0;
        for (int j = min(k, Size[x]); j >= 0; j--) {
            f[x][j][0] += f[y][0][0] + t;
            f[x][j][1] += f[y][0][0];
            for (int k = 1; k <= j; k++) {
                f[x][j][0] = min(f[x][j][0], f[y][k][0] + f[x][j - k][0] + t);
                f[x][j][0] = min(f[x][j][0], f[y][k][1] + f[x][j - k][0]);
                if (j == k)
                    continue;
                f[x][j][1] = min(f[x][j][1], f[y][k][0] + f[x][j - k][1]);
                f[x][j][1] = min(f[x][j][1], f[y][k][1] + f[x][j - k][1] + e[i].v);
            }
        }
    }
}

int main() {
    int x, y, z;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
    memset(f, 0x2f, sizeof(f));
    if (k + m - 1 > n)
        f[1][k][1] = -1;//无解
    else 
        treedp(1, 0);
    printf("%d\n", f[1][k][1]);
    return 0;
}