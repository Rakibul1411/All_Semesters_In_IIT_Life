#include<bits/stdc++.h>
#define Size 100
using namespace std;
char b[Size][Size];
void print_lcs(string x,int i,int j);
int main()
{
    string x,y;
    cout<<"Enter first string: ";
    cin>>x;
    cout<<"Enter second string: ";
    cin>>y;
    int c[x.size()+1][y.size()+1];
    int i,j;
    for(i=0;i<=x.size();i++)
        c[i][0]=0;
    for(j=0;j<=y.size();j++)
        c[0][j]=0;
    for(i=1;i<=x.size();i++)
    {
        for(j=1;j<=y.size();j++)
        {
            if(x[i-1]==y[j-1])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]='D';
            }
            else if(c[i-1][j]>=c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                b[i][j]='U';
            }
            else
            {
                c[i][j]=c[i][j-1];
                    b[i][j]='S';
            }
        }
    }
    for(i=1;i<=x.size();i++)
    {
        for(j=1;j<=y.size();j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    for(i=1;i<=x.size();i++)
    {
        for(j=1;j<=y.size();j++)
        {
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<c[x.size()][y.size()]<<endl;
    print_lcs(x,x.size(),y.size());
}
void print_lcs(string x,int i,int j)
{
    if(i==0||j==0)
    {
        return;
    }
    if(b[i][j]=='D')
    {
        print_lcs(x,i-1,j-1);
        cout<<x[i-1]<<" ";
        return;
    }
     if(b[i][j]=='U')
    {
        print_lcs(x,i-1,j);
    }
    else
    {
        print_lcs(x,i,j-1);
    }
    return;
}