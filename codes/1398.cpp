#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

long long n, ans, top;
long long a[100005], s[100005], w[100005];

int main() {
	while(cin >> n) {
		memset(s, 0, sizeof(s));
		ans = 0;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        a[n + 1] = top = 0;
		for (int i = 1; i <= n; i++) {
			if (s[top] < a[i]) {
                s[++top] = a[i];
                w[top] = 1;
            } 
			else {
				long long width = 0;
				while (s[top] > a[i]){
					width += w[top];
					ans = max(ans, width * s[top]);
					top--;
				}
                s[++top] = a[i];
				w[top] = width + 1;
			}
		}
		long long width = 0;
		while (s[top]){
			width += w[top];
			ans = max(ans, width * s[top]);
			top--;
		}
		cout << ans <<"\n";
	}
	return 0;
}