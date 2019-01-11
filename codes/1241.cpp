#include <iostream>
#include <algorithm>
using namespace std;

long long a[2000005] = {0}, b[10005] = {0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, s = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        s++;
        if (a[i + 1] != a[i]) {
            cout << a[i] << " " << s << "\n";
            s = 0;
        }
    }
    return 0;
}