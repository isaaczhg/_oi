/*
  ID:zxh18331
  PROG:milk2
  LANG:C++14
*/
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

struct node {
    int st, ed;
} a[5005];

bool cmp(const node &x, const node &y) {
    return x.st < y.st;
}

int main () {
    ifstream fin ("milk2.in");
    ofstream fout ("milk2.out");
    int n, maxx, minn, ans1 = 0, ans2 = 0;
    fin >> n;
    for (int i = 1; i <= n; i++)
        fin >> a[i].st >> a[i].ed;
    sort(a + 1, a + n + 1, cmp);
    maxx = a[1].ed, minn = a[1].st;
    ans1 = maxx - minn;
    for (int i = 2; i <= n; i++) {
        if (a[i].st > maxx) {
            ans1 = max(ans1, maxx - minn);
            ans2 = max(ans2, a[i].st - maxx);
            minn = a[i].st;
            maxx = a[i].ed;
        }
        else 
            maxx = max(maxx, a[i].ed);
    }
    fout << ans1 << " " << ans2 << "\n";
    return 0;
}