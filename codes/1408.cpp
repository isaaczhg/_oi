#include <iostream>
#include <cstdio>
using namespace std;

int n;

void init(int f[]) {
    int k = 0, K = 1, t = 1;
    f[0] = 0;
    for (int i = 1; i < 50005; i++) {
        f[i] = (f[i - 1] + t) % 10000;
        k++;
        if (k == K) {
            K++;
            k = 0;
            t = t * 2 % 10000;
        }
    }
}

int main() {
    int f[50005];
    init(f);
    while (cin >> n)
        cout << f[n] << "\n";
    return 0;
}