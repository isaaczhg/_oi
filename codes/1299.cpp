#include <algorithm>
#include <algorithm>
#include <iostream>
#define ll long long
#define Maxn 2000005
using namespace std;

struct node {
    int x, y, z, pos, id;
} a[Maxn], b[Maxn];
int s, w, num, cnt;
int ans[Maxn], c[Maxn];

bool cmp(const node &a, const node &b) {
    if (a.x == b.x && a.y == b.y)
        return a.pos < b.pos;
    else if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

inline int lowbit(int x) { return x & (-x); }

void add(int x, int d) {
    for (int i = x; i <= w; i += lowbit(i))
        c[i] += d;
}

int sum(int x) {
    int tmp = 0;
    for (int i = x; i; i -= lowbit(i))
        tmp += c[i];
    return tmp;
}

void cdq(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1, l1 = l, l2 = mid + 1;
    for (int i = l; i <= r; i++) {
        if (a[i].id <= mid && !a[i].pos)
            add(a[i].y, a[i].z);
        if (a[i].id > mid && a[i].pos)
            ans[a[i].pos] += sum(a[i].y) * a[i].z;
    }
    for (int i = l; i <= r; i++)
    if (a[i].id <= mid && !a[i].pos)
        add(a[i].y, -a[i].z);
    for (int i = l; i <= r; i++) {
        if (a[i].id <= mid)
            b[l1++] = a[i];
        else
            b[l2++] = a[i];
    }
    for (int i = l; i <= r; i++) a[i] = b[i];
    cdq(l, mid);
    cdq(mid + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int op, x, y, z, x1, y1, x2, y2;
    cin >> s >> w;
    while (1) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            num++;
            a[num] = (node){x, y, z, 0, num};
        } else if (op == 2) {
            cin >> x1 >> y1 >> x2 >> y2;
            x1--;
            y1--;
            ans[++cnt] = (x2 - x1) * (y2 - y1) * s;
            num++;
            a[num] = (node){x1, y1, 1, cnt, num};
            num++;
            a[num] = (node){x1, y2, -1, cnt, num};
            num++;
            a[num] = (node){x2, y1, -1, cnt, num};
            num++;
            a[num] = (node){x2, y2, 1, cnt, num};
        } else
            break;
    }
    sort(a + 1, a + num + 1, cmp);
    cdq(1, num);
    for (int i = 1; i <= cnt; i++)
        cout << ans[i] << "\n";
    return 0;
}