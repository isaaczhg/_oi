//选课
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node { int l, r, v; }a[305] = { 0 };
int son[305] = { 0 }, f[305][305] = { 0 };
int dp(int p, int t)//根为p，选t门课
{
	if (!p || !t)return 0;	//不选课
	if (f[p][t])return f[p][t];//记忆化必须在所有dp前
	if (a[p].r)f[p][t] = dp(a[p].r, t);//转为二叉树后，兄弟会变成第一个子树的子树 
	for (int i = 0; i <= t - 1; i++)
		f[p][t] = max(f[p][t], dp(a[p].l, i) + dp(a[p].r, t - i - 1) + a[p].v);//判断是选原来的子树（沿二叉树单枝）还是选现在的左右子树 
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
		if (!son[k])a[k].l = i;//如果无儿子，则为左儿子 
		else a[son[k]].r = i;//有儿子则为右儿子,可能成为儿子的儿子 
		son[k] = i;
	}
	printf("%d", dp(a[0].l, m));
	return 0;
}