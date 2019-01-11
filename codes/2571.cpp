#include <iostream>
#include <ctime>
using namespace std;

const int maxn = 100005;

struct treap {
    int data, l, r, ln, rn, pro;
} tree[maxn];

int m, tot, n, root, inf = 0x7fffffff/2;

void turnleft(int &t) {
    int p = tree[t].r;
    tree[t].r = tree[p].l;
    tree[t].rn = tree[p].ln;
    tree[p].l = t;
    tree[p].ln += tree[t].ln;
    t = p;
}

void turnright(int &t) {
    int p = tree[t].l;
    tree[t].l = tree[p].r;
    tree[t].ln = tree[p].rn;
    tree[p].r = t;
    tree[p].rn += tree[t].rn;
    t = p;
}

void insert(int &t, int s) {
    if (t == 0) {
        tot++;
        t = tot;
        tree[tot].data = s;
        tree[tot].l = tree[tot].r = 0;
        tree[tot].ln = tree[tot].rn = 1;
        tree[tot].pro = rand() % 10000;
        return;
    }
    if (s <= tree[t].data) {
        insert(tree[t].l, s);
        tree[t].ln++;
        if (tree[tree
        [t].l].pro < tree[t].pro)
            turnright(t);
    } else {
        insert(tree[t].r, s);
        tree[t].rn++;
        if (tree[tree[t].r].pro < tree[t].pro)
            turnleft(t);
    }
}

void del(int &t, int s) {
    if (s < tree[t].data) {
        tree[t].ln--;
        del(tree[t].l, s);
    } else if (tree[t].data < s) {
        tree[t].rn--;
        del(tree[t].r, s);
    } else if (tree[t].data == s) {
        if (tree[t].l == 0 && tree[t].r == 0) {
            t = 0;
            tree[t].data = 0;
            return;
        }
        int lp = inf, rp = inf;
        if (tree[t].l)
            lp = tree[tree[t].l].pro;
        if (tree[t].r)
            rp = tree[tree[t].r].pro;
        if (lp <= rp)
         {
            turnright(t);
            tree[t].rn--;
            del(tree[t].r, s);
        } else {
            turnleft(t);
            tree[t].ln--;
            del(tree[t].l, s);
        }
    }
}

int find_k(int t, int s, int sum) {
    if (sum + tree[t].ln == s)
        return tree[t].data;
    if (s < sum + tree[t].ln)
        return find_k(tree[t].l, s, sum);
    if (sum + tree[t].ln < s)
        return find_k(tree[t].r, s, sum + tree[t].ln);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand((unsigned)time(NULL));
    int s, k;
    char ch;
    cin >> n >> m;
    root = tot = 0;
    n = 0;
    for (int i = 1; i <= m; i++) {
        cin >> ch >> s;
        if (ch == 'i')
            insert(root, s);
        if (ch == 'd')
        {
            k = find_k(root, s, 0);
            cout << k << "\n";
            del(root, k);
        }
    }
    return 0;
}
