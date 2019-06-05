#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int n, p, h, m;
int c[10005], d[10005];
map<pair<int , int>, bool> vst;

int main() {
    int a, b;
    scanf("%d%d%d%d", &n, &p, &h, &m);
    for (int i = 1; i <= m ;i++) {
        scanf("%d%d", &a, &b);
        if (a > b)
            swap(a, b);
        if (vst[make_pair(a, b)])
            continue;
        d[a + 1]--, d[b]++;
        vst[make_pair(a, b)] = true;
    }
    for (int i = 1; i <= n; i++) {
        c[i] = c[i - 1] + d[i];
        printf("%d\n", h + c[i]);
    }
    printf("\n");
    return 0;
}