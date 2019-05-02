#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

long long ans;
long long n, m, suma, sumb;
priority_queue<long long> qa;
priority_queue<long long> qb;

int main() {
    //freopen("cut.in", "r", stdin);
    //freopen("cut.out", "w", stdout);
    long long x;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i < n; i++) {
        scanf("%lld", &x);
        qa.push(x);
    }
    for (int i = 1; i < m; i++) {
        scanf("%lld", &x);
        qb.push(x);
    }
    suma = 1, sumb = 1;
    while (!qa.empty() && !qb.empty()) {
        long long maxa  = qa.top(), maxb = qb.top();
        if (maxa >= maxb) {
            ans += maxa * suma;
            sumb++;
            qa.pop();
        } else {
            ans += maxb * sumb;
            suma++;
            qb.pop();
        } 
    }
    while (!qa.empty()) {
        ans += qa.top() * suma;
        qa.pop();
    }
    while (!qb.empty()) {
        ans += qb.top() * sumb;
        qb.pop();
    }
    printf("%lld", ans);
    return 0;
}