#include <cstdio>
#include <iostream>
using namespace std;


struct tree
{
    int a, b, sum;
}a[200000 * 4 + 1];
int ans = 0;

void build(int v, int l, int r) { 
    a[v].a = l;
    a[v].b = r;
    a[v].sum = 0;
    if(l == r)
        return;
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build((v << 1) + 1, mid + 1, r);
}

void add(int v, int l, int r) {
    if(l > a[v].b || r < a[v].a)
        return;
    if(l <= a[v].a && r >= a[v].b){
        a[v].sum++;
        return;
    }
    add(v << 1, l, r);
	add((v << 1) + 1, l, r);
}
void ask(int v, int x) {
    if(x < a[v].a || x > a[v].b)
        return;
    ans += a[v].sum;
    ask(v << 1, x);
    ask((v << 1) | 1, x);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int xc, n, l, r, c, p;
    cin >> xc >> n;
    build(1, 1, 200001);
    for (int i = 1; i <= n; i++){
        cin >> l >> r >> c;
        add(1, l + 100001, r + 100001 - 1);
    }
    cin >> p;
    ask(1, p + 100001);
    cout << ans << "\n";
    return 0;
}