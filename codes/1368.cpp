#include <iostream>
#include <cmath>
#define pi 3.14159265

using namespace std;

const double eps = 1e-9;

double l, x, y, w;
double calc(double a) { return l * cos(a) + (w - x * cos(a)) / sin(a); }

double three(double l, double r) {
    double mid, midmid;
    while (l + eps < r) {
        mid = l + (r - l) / 3.0;
        midmid = r - (r - l) / 3.0;
        if (calc(mid) > calc(midmid))
            r = midmid; //凸函数
        else
            l = mid;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> x >> y >> l >> w) {
        double l = 0, r = pi / 2, tmp; //弧度制
        tmp = three(l, r);
        if (calc(tmp) <= y)
            cout << "yes\n";
        else
            cout << "no\n";
    }
    return 0;
}