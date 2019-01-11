#include <iostream>
using namespace std;

const int Size = 10000005;
struct heap {
    int v, lc, rc;
} t[Size];
int v[Size], lc[Size], rc[Size], rt[Size], sz[Size];
int cnt;

int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (v[x] < v[y])
        swap(x, y);
    rc[x] = merge(rc[x], y);
    swap(lc[x], rc[x]);
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t, n, m, x, y, p, sc[20];
    char s[20];
    while (cin >> t) {
        sc[0] = sc[1] = 0;
        while (t--) {
            cin >> n >> m;
            cnt = rt[0] = rt[1] = sz[0] = sz[1] = 0;
            for (int i = 2; i <= m + 1; i++)
                cin >> sz[i];
            for (int i = 2; i <= m + 1; i++) {
                rt[i] = 0;
                for (int j = 1; j <= sz[i]; j++) {
                    cin >> v[++cnt];
                    lc[cnt] = rc[cnt] = 0;
                    rt[i] = merge(rt[i], cnt);
                }
            }
            for (int i = 1; i <= n; i++) {
                scanf("%s", s + 1);
                p = i & 1;
                if (s[1] == 't') {
                    scanf("%d", &x);
                    sz[p] += sz[x + 1];
                    sz[x + 1] = 0;
                    rt[p] = merge(rt[p], rt[x + 1]);
                }
                if (s[1] == 'C') {
                    if (v[rt[p]] > v[rt[!p]]) {
                        rt[p] = merge(rt[p], rt[!p]);
                        rt[!p] = 0;
                        sz[p] += sz[!p];
                        sz[!p] = 0;
                    } else if (v[rt[p]] < v[rt[!p]]) {
                        rt[!p] = merge(rt[p], rt[!p]);
                        rt[p] = 0;
                        sz[!p] += sz[p];
                        sz[p] = 0;
                    }
                }
                if (s[1] == 'L') {
                    rt[p] = merge(lc[rt[p]], rc[rt[p]]);
                    sz[p]--;
                }
                if (s[1] == 'x') {
                    scanf("%d", &x);
                    v[rt[p]] += x;
                }
                if (s[1] == 'E') {
                    scanf("%d", &x);
                    y = rt[p];
                    rt[p] = merge(lc[rt[p]], rc[rt[p]]);
                    v[y] = x;
                    lc[y] = rc[y] = 0;
                    rt[p] = merge(rt[p], y);
                }
            }
            printf("%d:%d\n", sz[1], sz[0]);
            if (sz[1] >= sz[0])
                sc[1]++;
            else
                sc[0]++;
        }
        if (sc[0] >= sc[1])
            printf("I will be back!!\n");
        else
            printf("Hahaha...I win!!\n");
    }
    return 0;
}