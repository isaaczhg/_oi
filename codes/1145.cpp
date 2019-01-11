#include <iostream>
#include <cstring>
using namespace std;

long long s[50005], q[50005], f[50005] = {0};
int n, L;

double slope(int i, int j) {//求斜率
    return double(f[j] + s[j] * s[j] - (f[i] + s[i] * s[i])) /
           double(s[j] - s[i]);
}

void dp() {
    int l = 1, r = 1;
    q[1] = 0;
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r && slope(q[l], q[l + 1]) < 2 * (s[i] - 1 - L))
            l++;
        //对于对首，如果G(q[l],q[l+1])<s[i],说明决策q[l+1]优于决策q[l],
        //则决策q[l]可以去掉
        int j = q[l];
        f[i] = f[j] + (s[i] - s[j] - 1 - L) * (s[i] - s[j] - 1 - L);
        while (l < r && slope(q[r - 1], q[r]) >= slope(q[r], i))
            r--;
        //对于队尾，如果G(q[r-1],q[r]>=G(q[r],i),说明决策q[r-1]优于决策q[r],
        //则决策q[r]可以去掉
        q[++r] = i;
    }
    cout << f[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x;
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        s[i] = s[i - 1] + x + 1;
    }
    dp();
    return 0;
}