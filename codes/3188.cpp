#include <iostream>
#include <stack>
#include <string>
using namespace std;

const int Mod = 10007;
stack<char> op;
int f[100010][2];
int topf;

void set() {
    topf++;
    f[topf][0] = f[topf][1] = 1;
}

void calc() {
    int f0, f1;
    if (op.top() == '+') {
        f0 = (f[topf][0] * f[topf - 1][0]) % Mod;
        f1 = (f[topf][0] * f[topf - 1][1]) % Mod +
             (f[topf][1] * f[topf - 1][0]) % Mod +
             (f[topf][1] * f[topf - 1][1]) % Mod;
    } else {
        f0 = (f[topf][0] * f[topf - 1][1]) % Mod +
             (f[topf][1] * f[topf - 1][0]) % Mod +
             (f[topf][0] * f[topf - 1][0]) % Mod;
        f1 = (f[topf][1] * f[topf - 1][1]) % Mod;
    }
    op.pop();
    topf--;
    f[topf][0] = f0, f[topf][1] = f1;
}

int main() {
    int l;
    string s;
    cin >> l >> s;
    s = '(' + s + ')';
    for (int i = 0; i <= s.length() - 1; i++) {
        switch (s[i]) {
        case '+':
            while (op.top() != '(')
                calc();
            op.push(s[i]);
            if (s[i + 1] != '(')
                set();
            break;
        case '*':
            while (op.top() == '*')
                calc();
            op.push(s[i]);
            if (s[i + 1] != '(')
                set();
            break;
        case '(':
            op.push(s[i]);
            if (s[i + 1] != '(')
                set();
            break;
        case ')':
            while (op.top() != '(')
                calc();
            op.pop();
            break;
        default:
            break;
        }
    }
    cout << f[topf][0] % Mod << '\n';
    return 0;
}