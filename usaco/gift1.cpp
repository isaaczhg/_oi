/*
ID: zxh18331
TASK: gift1
LANG: C++14               
*/
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int mon[15];
int np, m, n;
string name[15];
string p;

int main() {
    ifstream fin ("gift1.in");
    ofstream fout ("gift1.out");
    fin >> np;
    for (int i = 1; i <= np; i++)
        fin >> name[i];
    for (int i = 1; i <= np; i++) {
        fin >> p >> m >> n;
        for (int j = 1; j <= np; j++)
            if(name[j] == p) {
                if (!n) {
                    mon[j] += m;
                    break;
                }
                else {
                    mon[j] -= (m / n) * n;
                    for (int k = 1; k <= n; k++) {
                        fin >> p;
                        for (int q = 1; q <= np; q++) 
                            if (name[q] == p) {
                                mon[q] += m / n;
                                break;
                            }
                    }
                }
                break;
            }  
    }
    for (int i = 1; i <= np; i++)
        fout << name[i] << " " << mon[i] << "\n";
    return 0;
}