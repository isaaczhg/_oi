#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int f[3005][3005] = {0};
int main() {
    string s1, s2;
    int a1[3005], a2[3005], len1, len2;
    cin >> s1 >> s2;
    len1 = s1.length();
    len2 = s2.length();
    for (int i = 0; i < len1; i++)
        a1[i + 1] = s1[i];
    for (int i = 0; i < len2; i++)
        a2[i + 1] = s2[i];
    for (int i = 1; i <= len1; i++)
        for (int j = 1; j <= len2; j++) {
            if (a1[i] == a2[j])
                f[i][j] = f[i - 1][j - 1] + 1;
            else
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
        }
    cout << f[len1][len2];
}