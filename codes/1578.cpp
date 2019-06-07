#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

queue<int> q[1005];
deque<int> q0;
int n, k;
int t[1005][1005], num[1005];

int main() {
    int x;
    char s[10];
    while(true) {
        scanf("%d", &n);
        if (!n)
            return 0;
        printf("Scenario #%d\n", ++k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            for (int j = 1;j <= x; j++) { 
                scanf("%d", &t[i][j]);
                num[i]++;
            }
        }
        while(true) {
            scanf("%s", s);
            if (s[0] == 'E') {
                scanf("%d", &x);
                bool flag = 0;
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= num[i]; j++) {
                        if (t[i][j] == x) {
                            if (q[i].empty())
                                q0.push_back(i);
                            q[i].push(x);
                            flag = 1;
                            break;
                        }
                    }
                    if (flag)
                        break;
                }
            }
            if (s[0] == 'D') {
                int y = q[q0.front()].front();
                q[q0.front()].pop();
                if (q[q0.front()].empty())
                    q0.pop_front();
                printf("%d\n", y);
            }
            if (s[0] == 'S') {
                q0.clear();
                for (int i = 1; i <= n; i++)
                    while (!q[i].empty())
                        q[i].pop();
                break;
            }
        }
        printf("\n");
    }
    return 0;
}