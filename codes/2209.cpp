#include <cstdio>
#include <iostream>
using namespace std;

int n, m, x, head, tail, ans = -0x7fffffff / 2;
int s[200005], q[200005], num[200005];

int main() {
    scanf("%d%d", &n, &m);
    head = 1;
    tail = 1;
    q[head] = 0;
    num[head] = 0;
    for (int i = 1; i <= n; i++) {
        while (num[head] < i - m && head <= tail)
            head++;
        scanf("%d", &x);
        s[i] = s[i - 1] + x;
        if (ans < s[i] - q[head])
            ans = s[i] - q[head];
        while (s[i] <= q[tail] && tail > 0)
            tail--;
        tail++;
        q[tail] = s[i];
        num[tail] = i;
    }
    printf("%d\n", ans);
	return 0;
}