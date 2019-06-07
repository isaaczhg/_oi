#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

int a[1005], b[1005], f[1005];
int num, n, op, ed, len;
string s;

int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}

void chengdan(int a[], int k) {
    int i;
    for (i = 1; i <= a[0]; i++)
        a[i] = a[i] * k;
    for (i = 1; i <= a[0]; i++) {
        a[i + 1] = a[i + 1] + a[i] / 10;
        a[i] = a[i] % 10;
    }
    while (a[a[0] + 1] > 0) {
        a[0]++;
        a[a[0] + 1] += a[a[0]] / 10;
        a[a[0]] = a[a[0]] % 10;
    }
}

int zhuan(int i) {
    if (s[i] >= '0' && s[i] <= '9')
        return s[i] - '0';
    if (s[i] >= 'A' && s[i] <= 'Z')
        return s[i] - 'A' + 10;
    return s[i] - 'a' + 36;
}

int chudan(int a[], int b) {
    int i, d = 0;
    for (i = a[0]; i >= 1; i--) {
        d = d * 10 + a[i];
        a[i] = d / b;
        d = d % b;
    }
    while (a[0] > 0 && a[a[0]] == 0)
        a[0]--;
    return d;
}

int main() {
    int j, k;
    cin >> n;
    while (n--) {
        memset(a, 0, sizeof(a));
        cin >> op >> ed >> s;
        len = s.length();
        s = " " + s;
        for (j = 1; j <= len; j++) {
            int x;
            x = zhuan(j);
            chengdan(a, op);
            a[1] += x;
            num = 1;
            while (a[num] > 9)
                num++, a[num] += a[num - 1] / 10, a[num - 1] %= 10;
            if (num > a[0])
                a[0] = num;
        }
        printf("%d ", op);
        cout << s << endl;
        printf("%d ", ed);
        for (j = 1; a[0]; j++)
            f[j] = chudan(a, ed);
        for (k = j - 1; k >= 1; k--) {
            if (f[k] >= 10 && f[k] <= 35)
                printf("%c", char(f[k] + 55));
            else if (f[k] >= 36 && f[k] <= 61)
                printf("%c", char(f[k] + 61));
            else
                printf("%d", f[k]);
        }
        printf("\n\n");
    }
    return 0;
}
