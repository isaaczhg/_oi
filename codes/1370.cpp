#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

stack<char> s;
string ch;
int ans, maxx;

int main() {
    cin >> ch;
    for (int i = 0; i <= ch.length() - 1; i++) {
        if (ch[i] == '(' || ch[i] == '{' || ch[i] == '[')
            s.push(ch[i]);
        else {
            if (!s.empty()) {
            if ((ch[i] == ')' && s.top() == '(') || (ch[i] == '}' && s.top() == '{') || (ch[i] == ']' && s.top() == '[')) {
                ans += 2;
                s.pop();
            } else {
                maxx = max(maxx, ans);
                ans = 0;
                while(!s.empty())
                    s.pop();
            }
            } else {
            maxx = max(maxx, ans);
            ans = 0;
            }
        }
    }
    maxx = max(ans, maxx);
    printf("%d\n", maxx);
    return 0;
}