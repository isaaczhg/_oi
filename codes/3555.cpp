#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

struct cow {
    int st, ed;
} a[50005], s[50005];
int n, ans = 1, flag;

bool cmp(cow x, cow y) {
	return x.st < y.st;
}

    int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].st, &a[i].ed);
    sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= ans; j++) {
			flag = 0;
			if (a[i].st > s[j].ed) {
				s[j].ed = a[i].ed;
				flag = 1;
				break;
			}
		}
		if (!flag) {
			ans++;
			s[ans].ed = a[i].ed;
		}
	}
	printf("%d\n", ans);
	return 0;
}