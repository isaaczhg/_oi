#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct cow {
	int maxx, minn;
} a[2505];
struct fss {
	int num, spf;
} b[2505];
int c, l, ans;

bool cmp1(cow x, cow y) {
	return x.minn > y.minn;
}

bool cmp2(fss x, fss y) {
	return x.spf > y.spf;
}

int main() {
	scanf("%d%d", &c, &l);
	for (int i = 1; i <= c; i++)
		scanf("%d%d", &a[i].minn, &a[i].maxx);
	for (int i = 1; i <= l; i++)
		scanf("%d%d", &b[i].spf, &b[i].num);
	sort(a + 1, a + c + 1, cmp1);
	sort(b + 1, b + l + 1, cmp2);
	for (int i = 1; i <= c; i++) {
		for (int j = 1; j <= l; j++)
			if (a[i].minn <= b[j].spf && a[i].maxx >= b[j].spf && b[j].num) {
				ans++;
				b[j].num--;
				break;
			}			
	}
	printf("%d\n", ans);
	return 0;
}