#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

int n, x, ans;
stack<int> s;

int main() {
	scanf("%d", &n);
	s.push(0);
	while (n--) {
		scanf("%d", &x);
		while (x < s.top())
			s.pop();
		if (x > s.top()) {
			ans++;
			s.push(x);
		}
	}
	printf("%d\n", ans);
	return 0;
}