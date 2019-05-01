#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

string s;
int p1, p2, p3;

int compare(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;
    if (ch >= 'a' && ch <= 'z')
        return 0;
    return -1;
}

void solve(char x, char y) {
    int i, j;
    if (y - x == 1)
        return;
    if (y <= x) {
        cout << '-';
        return;
    }
    if (compare(x) != compare(y)) { //-两边不是同一类型
        cout << '-';
        return;
    }
    if (compare(x) == 0 && p1 == 2) {
        x = char(x - 32);
        y = char(y - 32);
    }
    if (compare(x) == -1 && p1 == 1) {
        x = char(x + 32);
        y = char(y + 32);
    }
    if (p1 == 3) {
        for (i = 1; i <= (y - x - 1) * p2; i++)
            cout << '*';
        return;
    }
    if (p3 == 1)
        for (i = 1; i <= y - x - 1; i++)
            for (j = 1; j <= p2; j++)
                cout << char(x + i);
    if (p3 == 2)
        for (i = y - x - 1; i >= 1; i--)
            for (j = 1; j <= p2; j++)
                cout << char(x + i);
}

int main() {
    // freopen("expand.in", "r", stdin);
    // freopen("expand.out", "w", stdout);
    int i = 0;
    cin >> p1 >> p2 >> p3 >> s;
    while (s[i] == '-') { //处理最前面的-
        cout << s[i];
        i++;
    }
    for (; i < s.length(); i++)
        if (s[i] == '-')
            solve(s[i - 1], s[i + 1]);
        else
            cout << s[i];
    return 0;
}