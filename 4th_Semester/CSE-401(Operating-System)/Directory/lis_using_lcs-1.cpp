#include<bits/stdc++.h>
using namespace std;
char b[100][100];
void print_lcs(int x[],int i,int j);
int main()
{
    int m,i,j;
    cout<<"Enter the number of input: ";
    cin>>m;
    int x[m],y[m];
    for(i=0;i<m;i++)
    {
        cin>>x[i];
        y[i]=x[i];
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<m-i-1;j++)
        {
            if(x[j]>x[j+1])
            {
                int temp=x[j];
                x[j]=x[j+1];
                x[j+1]=temp;
            }
        }
    }
    for(i=0;i<m;i++)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;
 int c[m+1][m+1];
    //char b[m+1][n+1];
    for(i=0;i<=m;i++)
    {
        c[i][0]=0;
    }
    for(j=0;j<=m;j++)
    {
        c[0][j]=0;
    }
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=m;j++)
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
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=m;j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=m;j++)
        {
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    print_lcs(x,m,m);
    cout<<endl;
}
void print_lcs(int x[],int i,int j)
{
    if(i==0||j==0)
        return;
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
