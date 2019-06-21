#include <cstdio>
#include <iostream>
using namespace std;

int vis[1005], b[1005], a[1005], map[1005][1005], s1[1005], s2[1005];
int n;
bool noans, flag;

void dp() {
    b[n] = a[n];
    for (int i = n - 1; i >= 1; i--)
        b[i] = min(b[i + 1], a[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n - 1; j++)
            if (a[i] < a[j] && a[i] > b[j + 1]) {
                map[i][j] = 1;
                map[j][i] = 1;
            }
}

void dfs(int x, int color) {
    vis[x] = color;
    for (int i = 1; i <= n; i++)
        if (map[x][i]) {
            if (!vis[i])
                dfs(i, 3 - color);
            if (vis[i] != 3 - color) {
                flag = 0;
                return;
            }
        }
}
bool color() {
    flag = 1;
    for (int i = 1; i <= n; i++)
        if (vis[i] == 0) {
            dfs(i, 1);
            if (!flag)
                return false;
        }
    return true;
}

void print() {
    int top1 = 0, top2 = 0, t = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 1) {
            top1++;
            s1[top1] = a[i];
            cout << 'a' << " ";
        } else {
            top2++;
            s2[top2] = a[i];
            cout << 'c' << " ";
        }
        while ((top1 > 0 && s1[top1] == t) || (top2 > 0 && s2[top2] == t)) {
            if (top1 > 0 && s1[top1] == t) {
                top1--;
                cout << 'b' << " ";
            } else {
                top2--;
                cout << 'd' << " ";
            }
            t++;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    dp();
    if (!color())
        printf("0\n");
    else
        print();
    return 0;
}
