//Cell Phone Network手机网络
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge { int to, next; }a[20005];
int n, cnt = 0, h[20005] = { 0 }, f[10005][3];
void addedge(int x, int y) {
	cnt++; a[cnt].to = y; a[cnt].next = h[x]; h[x] = cnt;
}
void dp(int x, int prt) {
	int y, minn, tmp = 0x7fffffff / 2;
	f[x][0] = 1;//自己 
	f[x][1] = 0;//儿子 
	f[x][2] = 0;//父亲 
	for (int i = h[x]; i; i = a[i].next) {
		y = a[i].to;
		if (y == prt)continue;
		dp(y, x);
		minn = min(f[y][0], f[y][1]);
		f[x][0] += min(minn, f[y][2]);
		f[x][1] += minn;
		f[x][2] += minn;
		tmp = min(tmp, f[y][0] - minn);//找出代价最小的一个儿子 
	}
	f[x][1] += tmp;
}
int main() {
	int x, y;
	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y); addedge(y, x);
	}
	dp(1, 1);
	printf("%d", min(f[1][0], f[1][1]));
}