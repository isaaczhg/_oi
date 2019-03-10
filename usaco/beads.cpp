/*
  ID:zxh18331
  PROG:beads
  LANG:C++14
*/
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

int N, len;
string s;

int mod(int n, int m) {
    while (n < 0)
        n += m;
    return n % m;
}

int nbreak(int p, int dir) {
    int i;
    int n;
    if (dir > 0)
        i = p;
    else
        i = mod(p - 1, len);
    char color = 'w';
    for (n = 0; n < len; i = mod(i + dir, len)) {
        if (color == 'w' && s[i] != 'w')
            color = s[i];
        else if (color != s[i] && s[i] != 'w')
            break;
        n++;
    }
    return n;
}

int main() {
    ifstream fin ("beads.in");
    ofstream fout ("beads.out");
    int n, m = 0;
    fin >> N >> s;
    len = s.length();
    for (int i = 0; i < len; ++i) {
        n = nbreak(i, 1) + nbreak(i, -1);
        if (n > m)
            m = n;
    }
    if (m > len)
        m = len;
    fout << m << "\n";
    return 0;
}