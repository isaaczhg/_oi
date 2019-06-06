#include <cstdio>
#include <iostream>
using namespace std;

int a[1005];
int t, k, bj, num;
char b[1005];

int compare(char a, char b) {
    if (a == '(' && b == ')')
        return 0;
    if (a == '(' || b == '(')
        return -1;
    if (a == '*' || a == '/' || b == '+' || b == '-' || b == ')')
        return 1;
    return -1;
}

int calc(int a, char ch, int b) {
    if (ch == '+')
        return a + b;
    if (ch == '-')
        return a - b;
    if (ch == '*')
        return a * b;
    if (ch == '/')
        return a / b;
	return 0;
}

int main() {
    string s;
    cin >> s;
    b[++num] = '(';
    s += ')';
    k = 0;
    while (k < s.length()) {
        if (s[k] >= '0' && s[k] <= '9') {
            t = 0;
            while (s[k] >= '0' && s[k] <= '9') {
                t = t * 10 + s[k] - '0';
                k++;
            }
            a[++a[0]] = t;
        }
        bj = compare(b[num], s[k]);
        if (bj == 0) {
            num--;
            k++;
        }
        if (bj == 1) {
            a[a[0] - 1] = calc(a[a[0] - 1], b[num], a[a[0]]);
            a[0]--;
            num--;
        }
        if (bj == -1) {
            b[++num] = s[k];
            k++;
        }
    }
    cout << a[a[0]];
    return 0;
}