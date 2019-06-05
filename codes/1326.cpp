#include <iostream>
#include <cstdio>
using namespace std;

int ans;
int c[15][15], num[15], mat[15];

int get_char(char ch) {
    if (ch == 'A')
        return 1;
    if (ch == '0')
        return 10;
    if (ch == 'J')
        return 11;
    if (ch == 'Q')
        return 12;
    if (ch == 'K')
        return 13;
    return ch - '0';
}

int main() {
	char ch;
    for (int i = 1; i <= 13; i++)
        for (int j = 4; j >= 1; j--) {
            cin >> ch;
            c[i][j] = get_char(ch);
        }
    num[13] = 4;
    while (num[13]) {
        int now = c[13][num[13]];
        num[13]--;
        while (now != 13) {
            mat[now]++;
            num[now]++;
            now = c[now][num[now]];
        }
    }
	for (int i = 1; i <= 12; i++)
    	ans += (mat[i] == 4);
    printf("%d\n", ans);
    return 0;
}