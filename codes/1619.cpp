#include <iostream>
using namespace std;

const int Maxn = 1000005;
long long l[Maxn], r[Maxn], s[Maxn], v[Maxn], dis[Maxn], siz[Maxn], stack[Maxn],
    totsize[Maxn], bcj[Maxn];
long long n, top;

inline long long Abs(long long x) {
    if (x < 0)
        return -x;
    return x;
}

long long merge(long long a, long long b) {
    if (!a || !b)
        return a + b;
    if (v[a] < v[b])
        swap(a, b);
    r[a] = merge(r[a], b);
    if (dis[r[a]] > dis[l[a]])
        swap(l[a], r[a]);
    if (!r[a])
        dis[a] = 0;
    else
        dis[a] = dis[r[a]] + 1;
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long ans = 0, pre = 1;
    cin >> n;
    for (int i = 1; i <= n; i++)
       cin >> v[i];
    for (int i = 1; i <= n; i++) {
        top++;
        stack[top] = i;
        totsize[top] = 1;
        siz[top] = 1;
        while (top > 1) {
            if (v[stack[top - 1]] <= v[stack[top]])
                break;
            else {
                siz[top - 1] += siz[top];
                totsize[top - 1] += totsize[top];
                stack[top - 1] = merge(stack[top - 1], stack[top]);
                top--;
                while (siz[top] * 2 > totsize[top] + 1) {
                    stack[top] = merge(l[stack[top]], r[stack[top]]);
                    siz[top]--;
                }
            }
        }
    }
    for (int i = 1, j; i <= top; i++) {
        for (j = pre; j <= pre + totsize[i] - 1; j++)
            ans += Abs(v[j] - v[stack[i]]);
        pre = j;
    }
    cout << ans << "\n";
    return 0;
}