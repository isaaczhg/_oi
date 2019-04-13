#include <cstdio>
#include <iostream>
using namespace std;

int n, sum;
int prime[205] = {0,   2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,
                  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,
                  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
                  151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};
long long f[205];

int main() {
    f[0] = 1;
    f[1] = 0;
    sum = 46;
    for (int i = 1; i <= sum; i++)
        for (int j = prime[i]; j <= 200; j++)
            f[j] += f[j - prime[i]];
    scanf("%d", &n);
    printf("%d\n", f[n]);
    return 0;
}