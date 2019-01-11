#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
const int maxn = 10001;
int n, m, block, qcnt, ccnt, L, R, head, ans;
int a[maxn], b[maxn], A[maxn], cnt[1000001];
char ch[5];
struct Ask {
    int l, r, lb, rb, tim, id;
} q[maxn]; //查询
// lb 表示左端所在的块，rb 同理，tim 记录查询前有多少次修改。
struct Modify {
    int x, y, last;
} c[maxn];
//修改操作
inline int Getblock(int num) { return (num - 1) / block + 1; }
bool cmp(Ask q, Ask qq) {
    if (q.lb == qq.lb) {
        if (q.rb == qq.rb)
            return q.tim < qq.tim;
        return q.rb < qq.rb;
    }
    return q.lb < qq.lb;
}
void Change(int x, int col) {
    if (L <= x && x <= R) //要修改的位置在当前区间
    {
        cnt[a[x]]--; // cnt[i]表示 i 颜色的个数
        if (cnt[a[x]] == 0)
            ans--;
        a[x] = col;
        if (cnt[a[x]] == 0)
            ans++;
        cnt[a[x]]++;
    } else
        a[x] = col; //要修改的位置不在当前区间
}
void Update(int x, int d) {
    int temp = cnt[a[x]];
    cnt[a[x]] += d;
    if (temp == 0 && cnt[a[x]] == 1)
        ans++;
    else if (temp == 1 && cnt[a[x]] == 0)
        ans--;
}
void MoDui() {
    L = 1;
    R = 0;
    head = 0; // L 和 R 是莫队算法的两边，head 是当前询问指针
    for (int i = 1; i <= qcnt; i++) {
        while (head > q[i].tim) //还原修改操作
        {
            Change(c[head].x, c[head].last);
            head--;
        }
        while (head < q[i].tim) //补齐修改操作
        {
            head++;
            Change(c[head].x, c[head].y);
        }
        //莫队算法的核心
        while (R < q[i].r)
            R++, Update(R, 1);
        while (L > q[i].l)
            L--, Update(L, 1);
        while (R > q[i].r)
            Update(R, -1), R--;
        while (L < q[i].l)
            Update(L, -1), L++;
        A[q[i].id] = ans;
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    block = sqrt(n);
    for (int i = 1; i <= m; i++) {
        scanf("%s", ch);
        if (ch[0] == 'R') {
            ccnt++;
            scanf("%d%d", &c[ccnt].x, &c[ccnt].y);
            //此处记录 b 数组以便还原修改
            c[ccnt].last = b[c[ccnt].x]; //记上一次的颜色
            b[c[ccnt].x] = c[ccnt].y;    //修改后的颜色
        } else {
            qcnt++;
            scanf("%d%d", &q[qcnt].l, &q[qcnt].r);
            //记录提问的相关信息
            q[qcnt].id = qcnt;
            q[qcnt].lb = Getblock(q[qcnt].l); //左端所在的块
            q[qcnt].rb = Getblock(q[qcnt].r); //右端所在的块
            q[qcnt].tim = ccnt;
        }
    }
    sort(q + 1, q + qcnt + 1, cmp); //排序
    MoDui();                        //莫队算法
    for (int i = 1; i <= qcnt; i++)
        printf("%d\n", A[i]);
    return 0;
}