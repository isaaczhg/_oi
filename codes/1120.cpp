#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;

LL f[20][20], c[20];

LL cal(LL x, int st, int flag) {// x为当前位,st为上一位,flag为是否达到上位的最大范围
    LL s = 0, ed;
    if (!x)
        return 1; //边界
    if (!flag && f[x][st] != -1)
        return f[x][st];
    ed = flag ? c[x] : 9; //如果flag为真，取c[x],否则取9
    for (LL i = st; i <= ed; i++) //该位从上一位到这一位的最大值开始枚举
        s += cal(x - 1, i, flag && i == ed);
    if (!flag)
        f[x][st] = s;
    return s;
}

LL ask(LL x) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    c[0] = 0;
    memset(c, 0, sizeof(c));
    while (x) {
        c[++c[0]] = x % 10;
        x /= 10;
    }
    return cal(c[0], 0, 1); //初始上一位为0
}

int main() {
    LL x, y;
    memset(f, -1, sizeof(f));
    while (cin >> x >> y) {
        cout << ask(y) - ask(x - 1) << "\n";
    }
    return 0;
}