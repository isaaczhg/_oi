//ʯ�Ӻϲ�
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int fmax[2005][2005] = {0}, fmin[2005][2005] = {0};
int main() {
    int n, minn = 0x7fffffff / 2, maxx = 0, a[2005], s[2005] = {0};
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        a[n + i] = a[i];
    for (int i = 1; i <= 2 * n; i++)
        s[i] = s[i - 1] + a[i];              //ǰ׺��
    for (int t = 1; t <= 2 * n - 1; t++)     //�׶�:�ڼ��κϲ�
        for (int i = 1; i <= 2 * n - t; i++) //״̬:�ϲ���ʼ��
        {
            int j = i + t; //�ϲ�������
            fmin[i][j] = 0x7fffffff / 2;
            fmax[i][j] = 0;
            for (int k = i; k <= j - 1; k++) //����:���ִ�
            {
                fmin[i][j] = min(fmin[i][j], fmin[i][k] + fmin[k + 1][j]);
                fmax[i][j] = max(fmax[i][j], fmax[i][k] + fmax[k + 1][j]);
            }
            fmin[i][j] = fmin[i][j] + s[j] - s[i - 1];
            fmax[i][j] = fmax[i][j] + s[j] - s[i - 1];
        }
    for (int i = 1; i <= n; i++) {
        minn = min(minn, fmin[i][n + i - 1]);
        maxx = max(maxx, fmax[i][n + i - 1]);
    }
    cout << minn << endl << maxx << endl;
}