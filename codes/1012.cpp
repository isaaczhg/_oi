//ѡ��
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node { int l, r, v; }a[305] = { 0 };
int son[305] = { 0 }, f[305][305] = { 0 };
int dp(int p, int t)//��Ϊp��ѡt�ſ�
{
	if (!p || !t)return 0;	//��ѡ��
	if (f[p][t])return f[p][t];//���仯����������dpǰ
	if (a[p].r)f[p][t] = dp(a[p].r, t);//תΪ���������ֵܻ��ɵ�һ������������ 
	for (int i = 0; i <= t - 1; i++)
		f[p][t] = max(f[p][t], dp(a[p].l, i) + dp(a[p].r, t - i - 1) + a[p].v);//�ж���ѡԭ�����������ض�������֦������ѡ���ڵ��������� 
	return f[p][t];
}
int main()
{
	int n, m, k, w, maxx = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &k, &w);
		a[i].v = w;
		if (!son[k])a[k].l = i;//����޶��ӣ���Ϊ����� 
		else a[son[k]].r = i;//�ж�����Ϊ�Ҷ���,���ܳ�Ϊ���ӵĶ��� 
		son[k] = i;
	}
	printf("%d", dp(a[0].l, m));
	return 0;
}