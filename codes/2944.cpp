#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int n, m;
int a[200005], last[2000005], st[200005], q[200005], f[200005][25];

void ST() {
	for (int i = 1; i <= n; i++)
		f[i][0] = q[i];
	for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

int ask(int l, int r) {
	if (l > r)
		return 0;
	int k;
    k = int(log(r - l + 1) / log(2));
    return max(f[l][k], f[r + 1 - (1 << k)][k]);
}


void find(int &p, int l, int r){
	if(st[l] == l)return p = l, void();
	if(st[r] <= l)return p=r+1, void();
	int L = l, R = r;
	while(L <= R){
		int mid = (L + R) >> 1;
		if(st[mid]<l)
			L = mid+1;
		else p = mid, R = mid-1;
	}
}


int main() {
	int l, r;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		st[i] = max(st[i - 1], last[a[i] + 1000005] + 1);
		q[i] = i - st[i] + 1;
		last[a[i] + 1000005] = i;
	}
	ST();
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &l, &r);
		int p;
		find(p, l + 1, r + 1);
		printf("%d\n", max(p - l - 1, ask(p, r + 1)));
	}
	return 0;
}