#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 50005;
const int base = 10000;

struct node {
    int x, n;
} a[maxn];

int b[maxn], n, mid, num, f[maxn][8], c[maxn][8], ans[8] = {0};

bool cmp(const node &a, const node &b) { return a.x < b.x; }

void read() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x;
        a[i].n = i;
        f[i][0] = f[i][1] = 1;
    }
    sort(a + 1, a + n + 1, cmp);
    num = 0, a[0].x = 0;
    for (int i = 1; i <= n; i++) //离散化
        if (a[i].x == a[i - 1].x)
            b[a[i].n] = num;
        else
            b[a[i].n] = ++num;
}

void gaojia(int a[], int b[]) {
    if (a[0] < b[0])
        a[0] = b[0];
    for (int i = 1; i <= a[0]; i++) {
        a[i] += b[i];
        a[i + 1] += a[i] / base;
        a[i] %= base;
    }
    if (a[a[0] + 1] > 0)
        a[0]++;
}

void print(int a[]) {
    cout << a[a[0]];
    for (int i = a[0] - 1; i >= 1; i--)
        for (int j = base / 10; j > 0; j /= 10)
            cout << a[i] / j % 10;
    cout << "\n";
}

inline int lowbit(int x) { return x & (-x); }

void add(int x, int v[]) {
    for (int i = x; i <= num; i += lowbit(i))
        gaojia(c[i], v);
}

void sum(int x, int t[]) {
    for (int i = x; i > 0; i -= lowbit(i))
        gaojia(t, c[i]);
}
void cal(int x) {
    for (int i = 1; i <= num; i++)
        memset(c[i], 0, sizeof(c[i]));
    add(b[x - 1], f[x - 1]);
    memset(f[x - 1], 0, sizeof(f[x - 1])); //初始化
    for (int i = x; i <= n; i++) {
        add(b[i], f[i]);
        memset(f[i], 0, sizeof(f[i]));
        sum(b[i] - 1, f[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    read();
    for (int i = 2; i <= 5; i++)
        cal(i);
    for (int i = 5; i <= n; i++)
        gaojia(ans, f[i]);
    print(ans);
    return 0;
}