#include <iostream>
#include <cstring>
using namespace std;

struct node {
    int dir;
    string name;
} a[200005];

int main() {
    int n, m, op, num, tmp = 1;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i].dir >> a[i].name;
    for (int i = 1; i <= n; i++)
        a[i + n] = a[i];
    /*for (int i = 1; i <= n * 2; i++)
        cout << a[i].name << " ";
    cout << "\n";*/
    while (m--) {
        cin >> op >> num;
        if (((!op) && (!a[tmp].dir)) || (op && a[tmp].dir)) {//向里，往左数, //向wai，往you数
            tmp += n;
            tmp -= num;
            if (tmp > n)
                tmp -= n;
            //cout << tmp << "nmsl" << "\n";
        }
        else if ((op && (!a[tmp].dir)) || ((!op) && a[tmp].dir)) {//向里，往右数, 向wai，往zuo数
            tmp += num;
            if (tmp > n)
                tmp -= n; 
            //cout << tmp << "nmsl" << "\n";
        }
    }
    cout << a[tmp].name << "\n";
    return 0;
}