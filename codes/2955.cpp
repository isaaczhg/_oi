#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n, len, num = 0;
int nxt[1000005];
string s;

int main() {
    scanf("%d", &n);
    while (n) {
        cin >> s;
        len = s.length();
        s = ' ' + s;
        printf("Test case #%d\n", ++num);
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
        printf("\n");
        scanf("%d", &n);
    }
    return 0;
}