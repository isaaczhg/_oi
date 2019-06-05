#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
int n, q;
int a[1000005], maxx[1000005][25], minn[1000005][25];

void st() {
    for (int i = 1; i <= n; i++) {
        maxx[i][0] = a[i]; 
    	minn[i][0] = a[i];
	}
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            maxx[i][j] = max(maxx[i][j - 1], maxx[i + (1 << (j - 1))][j - 1]);
        	minn[i][j] = min(minn[i][j - 1], minn[i + (1 << (j - 1))][j - 1]);
		}
}

int ask(int l, int r) {
    int k;
    k = int(log(r - l + 1) / log(2));
    return max(maxx[l][k], maxx[r + 1 - (1 << k)][k]) - min(minn[l][k], minn[r + 1 - (1 << k)][k]);
}

int main() {
    int l, r;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    st();
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &l, &r);
        printf("%d\n", ask(l, r));
    }
    return 0;
}