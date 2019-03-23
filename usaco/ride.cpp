/*
ID: zxh18331
TASK: ride
LANG: C++14               
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin ("ride.in");
    ofstream fout ("ride.out");
    string a, b;
    int s1 = 1, s2 = 1;
    fin >> a >> b;
    for (int i = 0; i <= a.length() - 1; i++)
        s1 *= a[i] - 'A' + 1;
    for (int i = 0; i <= b.length() - 1; i++)
        s2 *= b[i] - 'A' + 1;
    fout << ((s1 % 47 == s2 % 47) ? "GO\n":"STAY\n");
    return 0;
}