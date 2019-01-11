#include <iostream>
#include <cstring>
using namespace std;

const int Maxn = 1000005;

int n, m;
int r[Maxn], dj[Maxn], sj[Maxn], tj[Maxn], sum[Maxn];

bool check(int x) {
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= x; i++) {
        sum[sj[i]] += dj[i];
        sum[tj[i] + 1] -= dj[i];
    }
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1];
        if (sum[i] > r[i])
            return false;
    }
    return true;
}

int divide(int l, int r) {
    int mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else 
            r = mid - 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int maxn;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> r[i];
    for (int i = 1; i <= m; i++)
        cin >> dj[i] >> sj[i] >> tj[i];
    maxn = divide(0, m);
    if (maxn == m) {
        cout << 0 << "\n";
        return 0;
    }
    else 
        cout << -1 << "\n" << maxn + 1 << "\n";
    return 0;
}