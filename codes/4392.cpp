#include <iostream>
using namespace std;

int n, m, cnt, ans = 0;
int c[1000005], Next[1000005], ft[1000005], h[1000005], s[1000005], st[1000005];

void solve(int a, int b) {
    for (int i = h[a]; i; i = Next[i]) {
        if (c[i + 1] == b)
            ans--;
        if (c[i - 1] == b)
            ans--;
    }
    for (int i = h[a]; i; i = Next[i])
        c[i] = b;
    Next[st[a]] = h[b];
    h[b] = h[a];
    s[b] += s[a];
    h[a] = st[a] = s[a] = 0;
}

int main() { 
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        ft[c[i]] = c[i];
        if (c[i] != c[i - 1])
            ans++;
        if (!h[c[i]])
            st[c[i]] = i;
        s[c[i]]++;
        Next[i] = h[c[i]];
        h[c[i]] = i;
    }
    for (int i = 1; i <= m; i++) {
        int x, a, b;
        cin >> x;
        if (x == 2)
            cout << ans << "\n";
        else
        {
            cin >> a >> b;
            if (a == b)
                continue;
            if (s[ft[a]] > s[ft[b]])
                swap(ft[a], ft[b]);
            a = ft[a];
            b = ft[b];
            if (s[a] == 0)
                continue;
            solve(a, b);
        }
    }
    return 0;
}