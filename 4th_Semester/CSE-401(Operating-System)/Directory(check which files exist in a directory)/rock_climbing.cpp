#include<bits/stdc++.h>
#define size 100
using namespace std;
int a[size][size];
int c[size][size];
int row,column;
int minimum(int a,int b,int c);
void print_path(int m,int n);
int main()
{
    cout<<"Enter row and column of the rock: ";
    cin>>row>>column;
    int i,j;
    for(i=1;i<=row;i++)
    {
        for(j=1;j<=column;j++)
        {
            cin>>c[i][j];
        }
    }
    for(i=0;i<=row;i++)
    {
        a[i][0]=INT_MAX;
        a[i][column+1]=INT_MAX;
    }
    for(j=1;j<=column;j++)
    {
        a[0][j]=0;
        a[1][j]=c[1][j];
    }
    for(i=2;i<=row;i++)
    {
        for(j=1;j<=column;j++)
        {
            a[i][j]=c[i][j]+minimum(a[i-1][j-1],a[i-1][j],a[i-1][j+1]);
        }
    }
    //print rock adding
    for(i=1;i<=row;i++)
    {
        for(j=1;j<=column;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    int min=INT_MAX;
    int min_index;
    //getting min column index
    for(j=1;j<=column;j++)
    {
        if(a[row][j]<min)
        {
            min=a[row][j];
            min_index=j;
        }
    }
    print_path(row,min_index);
    cout<<endl;

}
int minimum(int a,int b,int c)
{
    if(a<b && a<c)
    {
        return a;
    }
    else if(b<a && b<c)
    {
        return b;
    }
    else 
    {
        return c;
    }
}
void print_path(int m,int n)
{
    if(m==0 || n==0 || n==column+1)
    {
        return;
    }
    else if(a[m-1][n-1]<a[m-1][n] && a[m-1][n-1]<a[m-1][n+1])
    {
        print_path(m-1,n-1);
    }
    else if(a[m-1][n]<a[m-1][n-1] && a[m-1][n]<a[m-1][n+1])
    {
        print_path(m-1,n);
    }
    else 
    {
        print_path(m-1,n+1);
    }
    cout<<c[m][n]<<" ";
}