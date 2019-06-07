#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int m, len, l1, l2, r1, r2;
char s[1000005];
unsigned long long f[1000005], p[1000005];

int main() {
    scanf("%s", s + 1);
    scanf("%d", &m);
    len = strlen(s + 1);
    p[0] = 1;
    for (int i = 1; i <= len; i++) {
        f[i] = f[i - 1] * 131 + (s[i] - 'a' + 1);
        p[i] = p[i - 1] * 131;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (f[r1] - f[l1 - 1] * p[r1 - l1 + 1] == f[r2] - f[l2 - 1] * p[r2 - l2 + 1])
            printf("Yes\n");
        else 
             printf("No\n");
    }
    return 0;
}