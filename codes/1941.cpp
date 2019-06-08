#include <cstdio>
#include <iostream>
using namespace std;

struct f {
    int a, b, c;
} w[10005];
struct heap {
    int v, f, n;
} a[10005], temp;
int num = 0;

void heapup() {
    int i;
    i = num;
    while (i > 1 && a[i].v < a[i / 2].v) {
        swap(a[i], a[i / 2]);
        i = i / 2;
    }
}
void heapdown() {
    int i = 1, j;
    while (i * 2 <= num) {
        j = i * 2;
        if (a[j].v > a[j + 1].v && j < num)
            j++;
        if (a[i].v > a[j].v) {
            swap(a[i], a[j]);
            i = j;
        } else
            break;
    }
}

int main() {
    int n, m, f, j;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &w[i].a, &w[i].b, &w[i].c);
        temp.v = w[i].a + w[i].b + w[i].c;
        temp.f = i;
        temp.n = 1;
        a[++num] = temp;
        heapup();
    }
    for (int i = 1; i <= m; i++) {
        printf("%d ", a[1].v);
        temp.f = f = a[1].f;
        temp.n = j = a[1].n + 1;
        temp.v = w[f].a * j * j + w[f].b * j + w[f].c;
        a[1] = temp;
        heapdown();
    }
    return 0;
}