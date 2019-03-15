#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int n, temp, ans, sum;
    scanf("%d", &n);
    ans = sum = 0;
    while (n--) {
        scanf("%d", &temp);
        ans ^= temp;
        if (temp > 1)
            sum++;
    }
    if (ans == 0) {
        if (sum)
            printf("win\n");
        else
            printf("lose\n");
    } else {
        if (sum)
            printf("win\n");
        else
            printf("lose\n");
    }
    return 0;
}
