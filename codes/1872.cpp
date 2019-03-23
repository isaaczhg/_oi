#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

struct que {
    int x, y, h;
};
int n, m;
int a[1005][1005], h[1005][1005];
bool vst[1005][1005];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
long long ans;

bool operator <(que a, que b) {
    return a.h > b.h; 
}
priority_queue <que> q;

void read() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <=n; i++)
        for(int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            h[i][j] = a[i][j];
        }
}

void add() {
    que x;
    for(int i = 1; i <=n; i++) {
        x = que {i, 1, a[i][1]};
        q.push(x);
        vst[i][1] = 1;
        x = que {i, m, a[i][m]};
        q.push(x);
        vst[i][m] = 1;
    }
    for(int i = 1; i <=m; i++) {
        x = que {1, i, a[1][i]};
        q.push(x);
        vst[1][i] = 1;
        x = que {n, i, a[n][i]};
        q.push(x);
        vst[n][i] = 1;
    }
}

void solve() {
    while (!q.empty()) {
        que t = q.top();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int tx = t.x, ty = t.y;
            tx += dx[i];
            ty += dy[i];
            if (tx < 1 || tx > n || ty < 1 || ty > m || vst[tx][ty])
                continue;
            vst[tx][ty] = 1;
            h[tx][ty] = max(h[tx][ty], t.h);
            que x = que{tx, ty, h[tx][ty]};
            q.push(x);
        }
    }
}

int main() {
    read();
    add();
    solve();
    for (int i = 1; i <=n; i++)
        for (int j = 1; j <= m; j++)
            ans += (long long)h[i][j] - a[i][j];
    printf("%lld\n", ans);
    return 0;
}