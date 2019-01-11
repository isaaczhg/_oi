#include <cstdio>
#include <iostream>
using namespace std;

int n, m, a[100005];

inline int lowbit(int x) { return x & (-x); }

void add(int x, int d) { 
    for (int i = x; i <= n; i += lowbit(i))
        a[i] += d;
}

int sum(int x) { 
    int ans = 0;
    for (int i = x; i > 0;i -= lowbit(i))
        ans += a[i];
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int i, d;
    string s;
    cin >> n >> m;
    while (m--) {
        cin >> s >> i >>d;
        if (s == "Add")
            add(i, d);
        if (s == "Sub")
            add(i, -d);
        if(s == "Ask")
            cout << sum(d) - sum(i - 1) << "\n";
    }
    return 0;
}