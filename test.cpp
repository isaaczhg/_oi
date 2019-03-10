#include <iostream>
#include <cstring>
using namespace std;

int n;
bool a[15][15], b[15][15], tmp[15][15];

void change1() {
    memcpy(tmp, b, sizeof(b));
    
}

int main() {
    char ch;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> ch;
            if (ch == '@')
                a[i][j] = 1;
            else 
                a[i][j] = 0;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> ch;
            if (ch == '@')
                b[i][j] = 1;
            else 
                b[i][j] = 0;
        }
    
}