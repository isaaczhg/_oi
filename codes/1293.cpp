#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

char map[750][750];

void dfs(int n, int x, int y) {
	int siz;
	if (n == 1) {
		map[x][y] = 'X';
		return;
	}
	siz = pow(3.0, n - 2);
	dfs (n - 1, x, y);//左上
	dfs(n - 1, x, y + siz * 2);//右上
	dfs(n - 1, x + siz, y + siz);//中间
	dfs(n - 1, x + siz * 2, y);//左下
	dfs(n - 1, x + siz * 2, y + siz * 2);//右下
}

int main() {
	int n, siz;
	while(cin >> n) {
		if (n == -1)
			return 0;
		siz = pow(3.0, n - 1);
		for (int i = 1; i <= siz; i++)
			for (int j = 1; j <= siz; j++)
				map[i][j] = ' ';
		dfs(n, 1, 1);
		for (int i = 1; i <= siz; i++) {
			for (int j = 1; j <= siz; j++)
				cout << map[i][j];
			cout << "\n";
		}
		cout << "-\n";
	}
	return 0;
}