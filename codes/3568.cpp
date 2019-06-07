#include <iostream>
#include <cstdio>
using namespace std;

int n, m;
int l[100005], r[100005];

int main() {
    char op;
    int s, t;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i++) {
        l[i] = i - 1;
        r[i] = i + 1;
    }
    for (int i = 1; i <= m; i++) {
        scanf("\n%c%d%d", &op, &s, &t);
        if (op == 'A') {
            r[l[s]] = r[s];
            l[r[s]] = l[s];//删除
            l[s] = l[t];
            r[s] = t;
            r[l[t]] = s;
            l[t] = s;
        }
        if (op == 'B') {
            r[l[s]] = r[s];
            l[r[s]] = l[s];
            r[s] = r[t];
            l[s] = t;
            l[r[t]] = s;
            r[t] = s;
        }
    }
    for (int i = 1, j = 0; i <= n; i++) {
        printf("%d\n", r[j]);
        j = r[j];
    }
    return 0;
}