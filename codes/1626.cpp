#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

typedef pair<int, int> heap;
priority_queue<heap, vector<heap>, greater<heap>> q;
int sum[100005], lt[100005], rt[100005];
int n, tmp, K, x, y, ans;

int main() {
    scanf("%d%d", &n, &K);
    y = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        sum[i] = x - y;
        y = x;
        if (i != 1)
            q.push(make_pair(sum[i], i));
        lt[i] = i - 1;
        rt[i] = i + 1;
    }
    lt[2] = rt[n] = 0;
    for (int i = 1; i <= K; i++) {
        while (q.top().first != sum[q.top().second])
            q.pop();
        tmp = q.top().second;
        q.pop();
        ans += sum[tmp];
        if (lt[tmp] != 0 && rt[tmp] != 0)
            sum[tmp] = sum[lt[tmp]] + sum[rt[tmp]] - sum[tmp];
        else
            sum[tmp] = 0x7fffffff / 2;
        sum[lt[tmp]] = sum[rt[tmp]] = 0x7fffffff / 2;
        lt[tmp] = lt[lt[tmp]];
        rt[tmp] = rt[rt[tmp]];
        lt[rt[tmp]] = tmp;
        rt[lt[tmp]] = tmp;
        q.push(make_pair(sum[tmp], tmp));
    }
    printf("%d\n", ans);
    return 0;
}