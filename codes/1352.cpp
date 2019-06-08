#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n, m, tot = 1;
int trie[1000005][26], cnt[1000005];
char s[1000005];

void insert(char *str) {
    int len = strlen(str), p = 1;
    for (int k = 0; k < len; k++) {
        int ch = str[k] - 'a';
        if (!trie[p][ch])
            trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    cnt[p]++;
}

int search(char *str) {
    int len = strlen(str), p = 1, ans = 0;
    for (int k = 0; k < len; k++) {
        p = trie[p][str[k] - 'a'];
        if (p == 0)
            break;
        ans += cnt[p];
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        insert(s);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%s", s);
        printf("%d\n", search(s));
    }
    return 0;
}