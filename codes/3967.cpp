#include <cstdio>
#include <iostream>
using namespace std;
int main() {
    int n, x, f;
    scanf("%d%d", &n, &f);
    for (int i = 1; i < n; i++) {
        scanf("%d", &x);
        f = f ^ x;
    }
    if (!f)
        printf("2\n");
    else
        printf("1\n");
    return 0;
}
