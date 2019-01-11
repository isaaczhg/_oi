#include <iostream>
#include <iomanip>
using namespace std;

double h, D, H, eps = 1e-8;

double calc(double x) { return (h * D - H * x) / (D - x) + x; }

double three(double left, double right) {
    while (left + eps < right) {
        double mid = left + (right - left) / 3.0;
        double midmid = right - (right - left) / 3.0;
        if (calc(mid) > calc(midmid))
            right = midmid;
        else
            left = mid;
    }
    return left;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> H >> h >> D;
        cout << fixed << setprecision(3) << calc(three(0, h / H * D)) << "\n";
    }
    return 0;
}