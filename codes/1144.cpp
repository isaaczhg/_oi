#include <iostream>
#include <cstring>
using namespace std;

long long s[500005], q[500005], f[500005] = {0};
int n, m;

double slope(int i, int j) {
    return double(f[j] + s[j] * s[j] - (f[i] + s[i] * s[i])) /
           double(2 * s[j] - 2 * s[i]);
}

void dp() {
    int l = 1, r = 1;
    q[1] = 0;
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r && slope(q[l], q[l + 1]) < s[i])
            l++;
        int j = q[l];
        f[i] = f[j] + (s[i] - s[j]) * (s[i] - s[j]) + m;
        while (l < r && slope(q[r - 1], q[r]) >= slope(q[r], i))
            r--;
        q[++r] = i;
    }
    cout << f[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x;
    while (cin >> n >> m) {
        memset(s, 0, sizeof(s));
        for (int i = 1; i <= n; i++) {
            cin >> x;
            s[i] = s[i - 1] + x;
        }
        dp();
    }
    return 0;
}