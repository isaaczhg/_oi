#include <iostream>
#include <cstring>
using namespace std;

int K, B, a[55];
long long f[55][55];

long long dfs(int pos, int n, int flag) {
    if (pos == 0)
        return (n == K);
    if (n > K)
        return 0;
    if (!flag && f[pos][n] != -1)
        return f[pos][n];
    int k = flag ? min(1, a[pos]) : 1;
    long long tp = 0;
    for (int i = 0; i <= k; i++)
        tp += dfs(pos - 1, n + (i ? 1 : 0), flag && (i == a[pos]));
    if (!flag)
        f[pos][n] = tp;
    return tp;
}

long long ask(int k, int b) {
    memset(f, -1, sizeof(f));
    int cnt = 0;
    while (k) {
        a[++cnt] = k % b;
        k /= b;
    } //转换为b进制处理数位
    return dfs(cnt, 0, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int L, R;
    cin >> L >> R >> K >> B;
    cout << ask(R, B) - ask(L - 1, B);
    return 0;
}
