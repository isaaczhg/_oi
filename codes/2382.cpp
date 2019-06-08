#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

priority_queue<int> qmax;
priority_queue<int, vector<int>, greater<int>> qmin;
int m, n, i, k = 1;
int a[2000005], b[2000005];

int main() {
    scanf("%d%d", &m, &n);
    for (int j = 1; j <= m; j++) 
        scanf("%d", &a[j]);
    for (int j = 1; j <= n; j++)
        scanf("%d", &b[j]);
    for (int j = 1; j <= m; j++) {
        if (i == 0 || a[j] >= qmax.top())
            qmin.push(a[j]);
        else {
            qmax.push(a[j]);
            qmin.push(qmax.top());
            qmax.pop();
        }
        while(j == b[k]) {
            i++, k++;
            printf("%d\n", qmin.top());
            qmax.push(qmin.top());
            qmin.pop();
        }
    }
    return 0;
}