//��ҩ
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, t[100005], v[100005], a[100005], f[100005] = {0}, sum[15][15] = {0},
                                           num = 0;
void complete(int T, int V) {
    for (int i = T; i <= m; i++)
        f[i] = max(f[i], f[i - T] + V);
}
void zeroonepack(int T, int V) {
    for (int i = m; i >= T; i--)
        f[i] = max(f[i], f[i - T] + V);
}
int main() {
    int x, y;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        sum[x][y]++;
    }
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (sum[i][j]) {
                num++;
                a[num] = sum[i][j]; //������ִ���
                t[num] = i;
                v[num] = j;
            }
    for (int i = 1; i <= num; i++) {
        if (a[i] * t[i] > m) {
            complete(t[i], v[i]);
            continue;
        } //������ִ���*ʱ�������ʱ�䣬��������ò��꣬�����Ϊ��ȫ����
        int k = 1;
        while (k <= a[i]) {
            zeroonepack(k * t[i], k * v[i]); //�����ƾ���������
            a[i] = a[i] - k;
            k *= 2;
        }
        if (a[i])
            zeroonepack(t[i] * a[i], v[i] * a[i]);
    }
    cout << f[m] << endl;
}