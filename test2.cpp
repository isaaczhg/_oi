#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int nxt[1000005];
int main() {
    int n, len, num = 0;
    string s;
    cin >> n;
    while (n) {
        cin >> s;
        len = s.length();
        s = ' ' + s;
        cout << "Test case #" << ++num << endl;
        memset(nxt, 0, sizeof(nxt));
        for (int i = 2, j = 0; i <= len; i++) {
            while (j > 0 && s[i] != s[j + 1])
                j = nxt[j];
            if (s[i] == s[j + 1])
                j++;
            nxt[i] = j;
        }
        for (int i = 2; i <= len; i++) {
            if (i % (i - nxt[i]) == 0 && nxt[i])
                printf("%d %d\n", i, i / (i - nxt[i]));
        }
        cout << endl;
        cin >> n;
    }
}