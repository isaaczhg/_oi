#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct rectangle {
    double x1, x2, y1, y2;
} a[100005];

int tot, num = 0;

void add(double x1, double x2, double y1, double y2) {
    tot++;
    a[tot].x1 = x1;
    a[tot].x2 = x2;
    a[tot].y1 = y1;
    a[tot].y2 = y2;
}

void cut(int j, double x1, double x2, double y1, double y2, int c) {
    double k1, k2;
    if (c == 1) {
        k1 = max(x1, a[j].x1);
        k2 = min(x2, a[j].x2);
        if(a[j].x1 < k1)
            add(a[j].x1, k1, a[j].y1, a[j].y2);
        if(a[j].x2 > k2)
            add(k2, a[j].x2, a[j].y1, a[j].y2);
        cut(j, k1, k2, y1, y2, 2);
    }
    if (c == 2) {
        k1 = max(y1, a[j].y1);
        k2 = min(y2, a[j].y2);
        if (a[j].y1 < k1)
            add(x1, x2, a[j].y1, k1);
        if (a[j].y2 > k2)
            add(x1, x2, k2, a[j].y2);
    }
}

void print() {
    double ans = 0;
    num++;
    cout << "Test case #" << num << "\n";
    for (int i = 1; i <= tot; i++) {
        ans += (a[i].x2 - a[i].x1) * (a[i].y2 - a[i].y1);
    }
    cout << "Total explored area: " << fixed << setprecision(2) << ans << "\n\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    double x1, x2, y1, y2;
    while (cin >> n) {
        if(!n)break;
        tot = 0;
        for (int i = 1; i <= n; i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            for (int j = 0; j <= tot; j++) {
                if (x1 >= a[j].x2 || x2 <= a[j].x1 || y1 >= a[j].y2 || y2 <= a[j].y1)continue;
                cut(j, x1, x2, y1, y2, 1);
                a[j] = a[tot];
                tot--;
                j--;
            }
            add(x1, x2, y1, y2);
        }
        print();
    }
    return 0;
}