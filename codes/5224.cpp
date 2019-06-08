#include <cstring>
#include <iostream>
using namespace std;

char s[110010], s_new[220020];
int p[220020];

int init() {
    int len = strlen(s);
    s_new[0] = '$';
    s_new[1] = '#';
    int j = 2;
    for (int i = 0; i < len; i++) {
        s_new[j++] = s[i];
        s_new[j++] = '#';
    }
    s_new[j] = '\0';
    return j;
}

int manacher() {
    int len = init(), max_len = -1, id, mx = 0;
    for (int i = 1; i < len; i++) {
        if (i < mx)
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1;
        while (s_new[i - p[i]] == s_new[i + p[i]])
            p[i]++;
        if (mx < i + p[i]) {
            id = i;
            mx = i + p[i];
        }
        max_len = max(max_len, p[i] - 1);
    }
    return max_len;
}

int main() {
    while (cin >> s)
        cout << manacher() << '\n';
    return 0;
}