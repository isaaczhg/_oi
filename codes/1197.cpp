#include <iostream>
using namespace std;

int l[105] = {0}, r[105] = {0};

void dfs(int x) {
    if (l[x])
        dfs(l[x]);
    if (r[x])
        dfs(r[x]);
    cout << x << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a[105] = {0};
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> l[i] >> r[i];
    dfs(1);
}