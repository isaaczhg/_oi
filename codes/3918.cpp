#include <algorithm>
#include <iostream>
using namespace std;

const int Maxn = 500005;
const int k = 2;
const int inf = 0x7fffffff / 2;
struct point {
    int x[3], minn[3], maxx[3];
} p[Maxn], a[Maxn * 2], P;
int n, m, d, root, ans, tot;
int c[Maxn * 2][2];

bool operator < (point a, point b) { return a.x[d] < b.x[d]; }

void pushup(int x) {
    int l = c[x][0], r = c[x][1];
    for (int i = 0; i < k; i++) {
        a[x].minn[i] = min(a[x].x[i], min(a[l].minn[i], a[r].minn[i]));
        a[x].maxx[i] = max(a[x].x[i], max(a[l].maxx[i], a[r].maxx[i]));
    }
}

void build(int &x, int l, int r, int depth) {
    if (l > r)
        return;
    x = ++tot;
    d = depth % k;
    int mid = (l + r) >> 1;
    nth_element(p + l, p + mid, p + r + 1);
    a[x] = p[mid];
    build(c[x][0], l, mid - 1, depth + 1);
    build(c[x][1], mid + 1, r, depth + 1);
    pushup(x);
}

int dis(point a) {
    int i, sum = 0;
    for (i = 0; i < k; i++)
        sum += abs(P.x[i] - a.x[i]);
    return sum;
}

int guess(int x) {
    if (!x)
        return inf;
    int sum = 0, i;
    for (i = 0; i < k; i++)
        sum += (!(a[x].minn[i] <= P.x[i] && P.x[i] <= a[x].maxx[i])) *
               min(abs(a[x].minn[i] - P.x[i]), abs(a[x].maxx[i] - P.x[i]));
    return sum;
}

void query(int x) {
    int dist[2], l, r;
    dist[0] = guess(c[x][0]);
    dist[1] = guess(c[x][1]);
    ans = min(ans, dis(a[x]));
    l = (dist[0] >= dist[1]);
    r = l ^ 1;
    if (dist[l] < ans)
        query(c[x][l]);
    if (dist[r] < ans)
        query(c[x][r]);
}

void insert(int &x, int depth) {
    if (!x) {
        a[x = ++tot] = P;
        pushup(x);
        return;
    }
    d = depth % k;
    if (P < a[x])
        insert(c[x][0], depth + 1);
    else
        insert(c[x][1], depth + 1);
    pushup(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < k; j++)
            cin >> p[i].x[j];
    for (int j = 0; j < k; j++) {
        a[0].minn[j] = inf;
        a[0].maxx[j] = -inf;
    }
    build(root, 1, n, 0);
    for (int i = 1; i <= m; i++) {
        cin >> t;
        ans = inf;
        for (int j = 0; j < k; j++)
            cin >> P.x[j];
        if (t ^ 1) {
            query(root);
            cout << ans << "\n";
        } else
            insert(root, 0);
    }
    return 0;
}
