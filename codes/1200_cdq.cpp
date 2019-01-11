#include <iostream>
using namespace std;

typedef long long ll;
const int Maxn = 5000005;

struct que {
    int type, id, v;
    bool operator<(const que &x) const {
        return id == x.id ? type < x.type : id < x.id;
    }
} a[Maxn];
int n, m;
int ans[Maxn];
que tmp[Maxn];

void cdq(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    int sum = 0;
    int p = l, q = mid + 1, o = l;
    while (p <= mid && q <= r) {
        if (a[p] < a[q]) {
            if (a[p].type == 1)
                sum += a[p].v;
            tmp[o++] = a[p++];
        } else {
            if (a[q].type == 2)
                ans[a[q].v] -= sum;
            else if (a[q].type == 3)
                ans[a[q].v] += sum;
            tmp[o++] = a[q++];
        }
    }
    while (p <= mid)
        tmp[o++] = a[p++];
    while (q <= r) {
        if (a[q].type == 2)
            ans[a[q].v] -= sum;
        else if (a[q].type == 3)
            ans[a[q].v] += sum;
        tmp[o++] = a[q++];
    }
    for (int i = l; i <= r; i++)
        a[i] = tmp[i];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int aid = 0, qid = 0;
    string op;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> op >> x >> y;
        if (op[1] == 'd') {
            a[++qid].type = 1;
            a[qid].id = x;
            a[qid].v = y;
        }
        if (op[0] == 'S') {
            a[++qid].type = 1;
            a[qid].id = x;
            a[qid].v = -y;
        }
        if (op[1] == 's') {
            a[++qid].type = 2;
            a[qid].id = x - 1;
            a[qid].v = ++aid;
            a[++qid].type = 3;
            a[qid].id = y;
            a[qid].v = aid;
        }
    }
    cdq(1, qid);
    for (int i = 1; i <= aid; i++)
        cout << ans[i] << "\n";
    return 0;
}