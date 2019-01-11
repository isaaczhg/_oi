#include <iostream>
#include <iomanip>
using namespace std;

const double eps = 1e-10; //注意精度

struct node {
    int x, y, z;
} s[10005];

double calc(int i, double x) { return s[i].x * x * x + s[i].y * x + s[i].z; }

double getmax(int n, double x) {
    double maxx = -100000000;
    for (int i = 1; i <= n; i++) //用n个函数分别计算
        maxx = max(maxx, calc(i, x));
    return maxx;

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b, c, t, n;
    double left, right, mid, midmid, ymid, ymidmid;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> s[i].x >> s[i].y >> s[i].z;
        left = 0;
        right = 1000;
        while (left + eps < right) {
            mid = left + (right - left) / 3;
            midmid = right - (right - left) / 3; //三分定义域;
                                 ymid = getmax(n, mid);
            ymidmid = getmax(n, midmid); //找出在n个函数中的最大值
            if (ymid < ymidmid)
                right = midmid; //凹函数
            else
                left = mid;
        }
        cout << fixed << setprecision(4) << ymid << "\n";
    }
}