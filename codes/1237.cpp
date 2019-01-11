#include<iostream>
using namespace std;

#define LL long long 

LL c[5005][5005];
int n, m;

inline int lowbit(int x) { return x & (-x); }

void add(int x, int y, int k) { 
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            c[i][j] += k;
}

LL sum(int x, int y) { 
    LL ans = 0; 
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            ans += c[i][j];
    return ans;
}
void ask(int x1, int y1, int x2, int y2) {
    cout << sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1) << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int x, y, w, z, k, ord;
    cin >> n >> m;
    while(cin >> ord) {
        if(ord == 1) {
            cin >> x >> y >> k;
            add(x, y, k);
        }
        else {
            cin >> w >> x >> y >> z;
            ask(w, x, y, z);
        }
    }
    return 0;
}