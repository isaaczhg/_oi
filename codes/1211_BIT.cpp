#include <cstdio>
#include <iostream>
using namespace std;

int n, c[1505][1505];
                
inline int lowbit(int x) { 
    return x & (-x); 
}

void add(int x, int y, int k) {
    for (int i = x; i <= n; i = i + lowbit(i))
        for (int j = y; j <= n; j = j + lowbit(j))
            c[i][j] += k;
}

int sum(int x, int y) {
    int ans = 0;
    for (int i = x; i > 0; i = i - lowbit(i))
        for (int j = y; j > 0; j = j - lowbit(j))
            ans += c[i][j];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t, x1, y1, x2, y2, k;
    while (1) {
        cin >> t;
        if (t == 0) {
            cin >> n;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    c[i][j] = 0;
        }
        if (t == 1) {
            cin >> x1 >> y1 >> k;
            x1++;
            y1++;
            add(x1, y1, k);
        }
        if (t == 2) {
            cin >> x1 >> y1 >> x2 >> y2;
            x1++;
            y1++;
            x2++;
            y2++;
            cout << (sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1)) << "\n";
        }
        if (t == 3)
            break;
    }
    return 0;
}
