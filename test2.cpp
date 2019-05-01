#include <cstring>
#include <iostream>
using namespace std;
int Ans, n, f[1002], St = 3, mod = 19211;
string S, x;
bool Number(string s, int L, int r, int &t) {
    int i;
    t = 0;
    for (i = L; i <= r; i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
        t = t * 10 + s[i] - '0';
    }
    return true;
}
int Another(string s, int L, int r) {
    int i, t = 1;
    for (i = L + 1; i <= r; i++) {
        if (s[i] == '(')
            t++;
        if (s[i] == ')')
            t--;
        if (t == 0)
            return i;
    }
}
int Findlow(string s, int L, int r) {
    int i, j = 0, k = 0, t = 0;
    for (i = r; i >= L; i--) {
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
int Cal(int a, char m, int b) {
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
int Tree(string s, int L, int r) {
    int t, pos, Left, Right;
    if (s[L] == '(' && Another(s, L, r) == r)
        return Tree(s, L + 1, r - 1);
    if (Number(s, L, r, t))
        return t;
    if (L == r && s[L] == 'a')
        return Ans;
    pos = Findlow(s, L, r);
    Left = Tree(s, L, pos - 1);
    Right = Tree(s, pos + 1, r);
    t = Cal(Left, s[pos], Right);
    return t;
}
void Killspace(string &a) //去除掉 a 中多余的空白
{
    string tmp = "";
    for (int i = 0; i < a.length(); i++)
        if (a[i] != ' ')
            tmp += a[i];
    a = tmp;
}
int main() {
    int i, t;
    getline(cin, S); //读入一行
    Killspace(S);    //去掉中间的空格
    for (Ans = 0; Ans <= St; Ans++)
        f[Ans] = Tree(S, 0, S.length() - 1); //带值计算
    cin >> n;
    getline(cin, x);
    for (i = 1; i <= n; i++) //对于每个表达式分别计算
    {
        getline(cin, x);                //读入一行
        Killspace(x);                   //去掉中间的空格
        for (Ans = 0; Ans <= St; Ans++) //带值计算
        {
            t = Tree(x, 0, x.length() - 1);
            if (t != f[Ans])
                break; //不相等
        }
        if (Ans > St)
            cout << char(i + 'A' - 1);
    }
    return 0;
}