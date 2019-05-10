#include <cstring>
#include <iostream>
using namespace std;

int ans, n, f[1002], st = 3, mod = 19211;
string S, x;

bool number(string s, int l, int r, int &t) {
    int i;
    t = 0;
    for (i = l; i <= r; i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
        t = t * 10 + s[i] - '0';
    }
    return true;
}

int another(string s, int l, int r) {
    int i, t = 1;
    for (i = l + 1; i <= r; i++) {
        if (s[i] == '(')
            t++;
        if (s[i] == ')')
            t--;
        if (t == 0)
            return i;
    }
}

int find_low(string s, int l, int r) {
    int j = 0, k = 0, t = 0;
    for (int i = r; i >= l; i--) {
        if (s[i] == 'a' || (s[i] <= '9' && s[i] >= '0'))
            continue;
        if (s[i] == ')') {
            t++;
            continue;
        }
        if (s[i] == '(') {
            t--;
            continue;
        }
        if ((s[i] == '+' || s[i] == '-') && t == 0)
            return i;
        if (k == 0 && t == 0 && (s[i] == '*' || s[i] == '/')) {
            k = i;
            continue;
        }
        if (j == 0 && t == 0 && s[i] == '^') {
            j = i;
            continue;
        }
    }
    if (k != 0)
        return k;
    else
        return j;
}

int cal(int a, char m, int b) {
    int t = 1;
    switch (m) {
    case '+':
        return ((a + b) % mod + mod) % mod;
    case '-':
        return ((a - b) % mod + mod) % mod;
    case '*':
        return (a * b % mod + mod) % mod;
    case '^':
        for (int i = 1; i <= b; i++)
            t = (a * t % mod + mod) % mod;
        return t;
    }
}

int tree(string s, int l, int r) {
    int t, pos, left, right;
    if (s[l] == '(' && another(s, l, r) == r)
        return tree(s, l + 1, r - 1);
    if (number(s, l, r, t))
        return t;
    if (l == r && s[l] == 'a')
        return ans;
    pos = find_low(s, l, r);
    left = tree(s, l, pos - 1);
    right = tree(s, pos + 1, r);
    t = cal(left, s[pos], right);
    return t;
}

void del_space(string &a) {
    string tmp = "";
    for (int i = 0; i < a.length(); i++)
        if (a[i] != ' ')
            tmp += a[i];
    a = tmp;
}

int main() {
    int t;
    getline(cin, S);
    del_space(S);
    for (ans = 0; ans <= st; ans++)
        f[ans] = tree(S, 0, S.length() - 1);
    cin >> n;
    getline(cin, x);
    for (int i = 1; i <= n; i++) {
        getline(cin, x);
        del_space(x);
        for (ans = 0; ans <= st; ans++) {
            t = tree(x, 0, x.length() - 1);
            if (t != f[ans])
                break;
        }
        if (ans > st)
            cout << char(i + 'A' - 1);
    }
    return 0;
}