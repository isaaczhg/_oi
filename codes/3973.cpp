#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n;
int sg[2005];

int dfs(int x) {
    int g[2005] = {0};
    if (x < 0)
        return sg[x];
    if (sg[x] >= 0)
        return sg[x];
    for (int i = 1; i <= x; i++)
        g[dfs(i - 3) ^ dfs(x - i - 2)] = 1;
    for (int i = 0; ; i++)
        if (!g[i]) {
            sg[x] = i;
            break;
        }
    return sg[x];
}

int main() {
    memset(sg, -1, sizeof(sg));
    scanf("%d", &n);
    dfs(n);
    if (sg[n])
        printf("1\n");
    else 
        printf("2\n");
    return 0;
}