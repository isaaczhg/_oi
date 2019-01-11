#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 20005;
struct rectangle{
    int x1,y1,x2,y2;
}a[maxn], now;
int k,m,n,tot,x1,x2,v,num;

void add(int x1,int y1,int x2,int y2)
{
    tot++;
    a[tot].x1=x1;
    a[tot].y1=y1;
    a[tot].x2=x2;
    a[tot].y2=y2;
}
void cut(int x1,int y1,int x2,int y2,int c)
{
    int k1,k2;
    if(c==1)
    {
        k1=max(x1,now.x1);
        k2=min(x2,now.x2);
        if(x1<k1)add(x1,y1,k1,y2);
        if(k2<x2)add(k2,y1,x2,y2);
        cut(k1,y1,k2,y2,c+1);
    }
    if(c==2)
    {
        k1=max(y1,now.y1);
        k2=min(y2,now.y2);
        if(y1<k1)add(x1,y1,x2,k1);
        if(k2<y2)add(x1,k2,x2,y2);
        num+=(x2-x1)*(k2-k1);
    }
}
bool xiangjiao(int x1,int x2,int x3,int x4)
{
    if(x1>=x4 || x3>=x2)return false;
    else return true;
}

void fxxk_alien()
{
    int tot1;
    num=0;
    tot1=tot;
    for(int i=0;i<=tot1;i++)
    {
        if(xiangjiao(a[i].x1,a[i].x2,now.x1,now.x2)&&
          xiangjiao(a[i].y1,a[i].y2,now.y1,now.y2))
        {
            cut(a[i].x1,a[i].y1,a[i].x2,a[i].y2,1);
            a[i]=a[tot1];
            a[tot1]=a[tot];
            tot--;
            tot1--;
            i--;
        }
    }
    cout<<num<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n>>m;
    memset(a,0,sizeof(a));
    tot=0;
    for(int i=1;i<=m;i++)
    {
        cin>>k>>x1>>x2>>v;
        now.x1=x1-1;
        now.y1=0;
        now.x2=x2;
        now.y2=v;
        if(k==1)
            add(now.x1,now.y1,now.x2,now.y2);
        else fxxk_alien();
    }
}