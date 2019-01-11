#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;

int dp[105][105], a[105], mod, l, r;

int cal(int pos, int pre, bool flag) {// pos位数,pre前面的余数
    if (pos == 0)
        return pre == 0;
    if (!flag && dp[pos][pre] != -1)
        return dp[pos][pre];
    LL res = 0, ed;
    ed = flag ? a[pos] : 9;
    for (int i = 0; i <= ed; i++) {//当前位的取值范围
    
        int new_pre = (pre + i) % mod;
        res += cal(pos - 1, new_pre, flag && i == ed);
    }
    if (!flag)
        dp[pos][pre] = res;
    return res;
}

LL solve(int n) {
    int len = 0;
    while (n) {
        a[++len] = n % 10;
        n /= 10;
    } //分离各位
    return cal(len, 0, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> l >> r >> mod) {
        memset(dp, -1, sizeof(dp));
        cout << solve(r) - solve(l - 1) << "\n";
    }
    return 0;
}