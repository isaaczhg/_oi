#include <iostream>
#include <ctime>
using namespace std;

const int inf = 0x7fffffff/2;

struct atp {
    int data, pro, num, l, r, ln, rn;
} tree[2000005];

int n, m, p = 0, tot = 0;

void turnleft(int &p) {
    int t = tree[p].r;
    tree[p].r = tree[t].l;
    tree[t].l = p;
    tree[p].rn = tree[t].ln;
    tree[t].ln = tree[p].ln + tree[p].rn + 1;
    p = t;
}

void turnright(int &p) {
    int t;
    t = tree[p].l;
    tree[p].l = tree[t].r;
    tree[t].r = p;
    tree[p].ln = tree[t].rn;
    tree[t].rn = tree[p].ln + tree[p].rn + 1;
    p = t;
}

void insert(int &p, int x) {
    if (!p) {
        tot++;
        p = tot;
        tree[p].data = x;
        tree[p].l = tree[p].r = 0;
        tree[p].ln = tree[p].rn = 0;
        tree[p].pro = rand() % 10000;
        return;
    }
    if (x <= tree[p].data) {
        insert(tree[p].l, x);
        tree[p].ln++;
        if (tree[tree[p].l].pro < tree[p].pro)turnright(p);
    } else {
        insert(tree[p].r, x);
        tree[p].rn++;
        if (tree[tree[p].r].pro < tree[p].pro)turnleft(p);
    }
}

void del(int &p, int x) {
    if (!p)
        return;
    if (x < tree[p].data) {
        tree[p].ln--;
        del(tree[p].l, x);
    } else if (x > tree[p].data) {
        tree[p].rn--;
        del(tree[p].r, x);
    } else {
        if (!tree[p].l && !tree[p].r) {
            p = 0;
            return;
        }
        int lp = inf, rp = inf;
        if (tree[p].l)
            lp = tree[tree[p].l].pro;
        if (tree[p].r)
            rp = tree[tree[p].r].pro;
        if (lp <= rp) {
            turnright(p);
            tree[p].rn--;
            del(tree[p].r, x);
        } else {
            turnleft(p);
            tree[p].ln--;
            del(tree[p].l, x);
        }
    }
}

void find_k(int p, int k) {
    if (tree[p].ln + tree[p].rn + 1 < k) {
        cout << 0 << "\n";
        return;
    }
    if (tree[p].ln + 1 == k) {
        cout << tree[p].data << "\n";
        return;
    }
    if (k <= tree[p].ln)
        find_k(tree[p].l, k);
    else 
        find_k(tree[p].r, k - tree[p].ln - 1);
}

bool find (int p, int x) {
    if (p == 0)
        return false;
    else if (x == tree[p].data)
        return true;
    else if (x < tree[p].data)
        return find(tree[p].l, x);
    else 
        return find(tree[p].r, x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand((unsigned)time(NULL));
    int x, c;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (find(p, x))
            continue;
        else 
            insert(p, x);
    }
    while (m--) {
        cin >> c >> x;
        if (c == 1) {
            if (find(p, x))
                continue;
            else 
                insert(p, x);
        }
        if (c == 2) {
            if (!find(p, x))
                continue;
            else 
                del(p, x);
        }
        if (c == 3) 
            find_k(p, x);
    }
    return 0;
}