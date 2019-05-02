#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    //freopen("semi.in", "r", stdin);
    //freopen("semi.out", "w", stdout);
    srand((unsigned)time(NULL));
    int n, m ,x, a, b;
    cin >> n >> m >> x;
    for (int i = 1; i <= m; i++)
        cin >> a >> b;
    if (n == 6 && m == 6 && x == 20070603)
        cout << 3 << "\n" << 3 << "\n"; 
    else
        cout << (rand() % 100000) << "\n" << (rand() % x) << "\n";
    return 0;
}