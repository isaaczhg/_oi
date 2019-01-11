#include <cstdio>
#include <iostream>
using namespace std;

struct point {
    int x1, x2, y1, y2, c;
} b[20005];

struct tree {
    int a, b, c;
} a[20000 * 4 + 1];

int A, B, N;
int lx[20005], px[20005] = {0}, ans[20005] = {0};

void read() {
    int i;
    scanf("%d%d%d", &A, &B, &N);
    for (i = 1; i <= N; i++) {
        scanf("%d%d%d%d%d", &b[i].x1, &b[i].y1, &b[i].x2, &b[i].y2, &b[i].c);
        lx[b[i].x1] = 1;
        lx[b[i].x2] = 1;
    }
    for (i = 0; i <= A; i++)
        if (lx[i])
            px[++px[0]] = i; //离散化
}
void build(int v, int l, int r) 
{
    a[v].a = l;
    a[v].b = r;
    a[v].c = 0;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(2 * v, l, mid);
    build(2 * v + 1, mid + 1, r);
}
void insert(int v, int l, int r, int color) {
    if (l > a[v].b || r < a[v].a)
        return; 
    if (a[v].c > 0)
        return; 
    if (l <= a[v].a && r >= a[v].b && a[v].c != -1) {
        a[v].c = color;
        return;
    } 
    insert(2 * v, l, r, color);
    insert(2 * v + 1, l, r, color);
    a[v].c = -1; 
}
void Find(int v, int i) {
    if (a[v].c == 0)
        return; 
    if (a[v].c > 0) {
        ans[a[v].c] += (a[v].b - a[v].a + 1) * (px[i + 1] - px[i]);
        a[v].c = 0; //清0,为下一个区间的线段树作准备
        return;
    }
    Find(2 * v, i);
    Find(2 * v + 1, i);
    a[v].c = 0; //清0,为下一个区间的线段树作准备
}
void Solve() {
    int i, j;
    for (i = 1; i < px[0]; i++)
    {
        for (j = N; j >= 1; j--)
            if (b[j].x1 <= px[i] && b[j].x2 > px[i]) //跨越区间
                insert(1, b[j].y1, b[j].y2 - 1, b[j].c);
        Find(1, i);
    }
}
void Print() {
    int i;
    ans[1] = A * B;
    for (i = 2; i <= 10000; i++)
        ans[1] -= ans[i];
    for (i = 1; i <= 10000; i++)
        if (ans[i])
            printf("%d %d\n", i, ans[i]);
}
int main() {
    read();             
    build(1, 0, B - 1);
    Solve();
    Print();
}

//矩形切割
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 100001;

struct node {
    int x1, x2, y1, y2, c;
} a[maxn];

int tot = 0, n, m, q, c = 1, s[2505] = {0};

void add(int x1, int y1, int x2, int y2, int c) //添加矩形
{
    tot++;
    a[tot].x1 = x1;
    a[tot].x2 = x2;
    a[tot].y1 = y1;
    a[tot].y2 = y2;
    a[tot].c = c;
}

void cut(int v, int x1, int y1, int x2, int y2, int cmd) {
    int k1, k2;
    if (cmd == 0) // x方向上的切割
    {
        k1 = max(x1, a[v].x1); //(x1,x2),(x3,x4)交集左边界
        k2 = min(x2, a[v].x2); //(x1,x2),(x3,x4)交集右边界
        if (a[v].x1 < k1)
            add(a[v].x1, a[v].y1, k1, a[v].y2, a[v].c); //加入矩形(x1,y1,k1,y2)
        if (k2 < a[v].x2)
            add(k2, a[v].y1, a[v].x2, a[v].y2, a[v].c); //加入矩形(k2,y1,x2,y2)
        cut(v, k1, y1, k2, y2,
            1); //对切剩的矩形(k1,y1,k2,y2)进行 y 方向上的切割
    }
    if (cmd == 1) // y方向上的切割
    {
        k1 = max(y1, a[v].y1); //(y1,y2),(y3,y4)交集的上边界
        k2 = min(y2, a[v].y2); //(y1,y2),(y3,y4)交集的下边界
        if (a[v].y1 < k1)
            add(x1, a[v].y1, x2, k1, a[v].c); //加入矩形(x1,y1,x2,k1)
        if (k2 < a[v].y2)
            add(x1, k2, x2, a[v].y2, a[v].c); //加入矩形(x1,k2,x2,y2)
    }
}
void solve() {
    int x1, y1, x2, y2, color;
    cin >> n >> m >> q;
    add(0, 0, n, m, 1);
    for (int i = 1; i <= q; i++) {
        cin >> x1 >> y1 >> x2 >> y2 >> color;
        c = max(c, color);
        for (int j = 1; j <= tot; j++) {
            if (a[j].x1 >= x2 || a[j].y1 >= y2 || a[j].x2 <= x1 ||
                a[j].y2 <= y1)
                continue;
            cut(j, x1, y1, x2, y2, 0);
            a[j] = a[tot];
            tot--;
            j--;
        }
        add(x1, y1, x2, y2, color);
    }
    for (int i = 1; i <= tot; i++)
        s[a[i].c] += (a[i].x2 - a[i].x1) * (a[i].y2 - a[i].y1);
    for (int i = 1; i <= c; i++)
        if (s[i])
            cout << i << " " << s[i] << "\n";
}
int main() {
    solve();
    return 0;
}
