#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;

LL f[20][2], c[20];

LL cal(LL x, int y,
       int flag) // x为当前位,y为上一位是否为6,flag为是否达到该位的最大范围
{
    if (!x)
        return 1; //边界
    if (!flag && f[x][y] != -1)
        return f[x][y];
    LL s = 0, k;
    k = flag ? c[x] : 9; //如果flag为真，取c[x],否则取9
    for (LL i = 0; i <= k; i++) {
        if (i == 4 || (y == 1 && i == 2))
            continue;
        s += cal(x - 1, i == 6, flag && i == k);
    }
    if (!flag)
        f[x][y] = s;
    return s;
}

LL ask(LL x) {
    c[0] = 0;
    while (x) {
        c[++c[0]] = x % 10;
        x /= 10;
    }
    return cal(c[0], 0, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    LL x, y;
    cin >> x >> y;
    memset(f, -1, sizeof(f));
    while (1) {
        if (!x && !y)
            return 0;
        cout << ask(y) - ask(x - 1) << "\n";
        cin >> x >> y;
    }
    return 0;
}