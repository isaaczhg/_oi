#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    //freopen("sum.in", "r", stdin);
    //freopen("sum.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 1) {
        printf("1\n");
        long long sum = 1;
        for (int i = 1; i <= m; i++)
            sum *= i;
        printf("%lld\n", sum); 
    }
    return 0;
}