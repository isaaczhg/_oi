//合并果子
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
priority_queue< int, vector<int>, greater<int> >q;
int main() {
	long long  n, x, l, r, sum = 0;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &x);
		q.push(x);
	}
	for (int i = 1; i <= n - 1; i++) {
		l = q.top(); q.pop();
		r = q.top(); q.pop();
		sum += (l + r);
		q.push(l + r);
	}
	printf("%lld", sum);
}