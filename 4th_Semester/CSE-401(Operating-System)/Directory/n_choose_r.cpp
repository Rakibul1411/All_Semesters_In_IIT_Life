#include<bits/stdc++.h>
#define SIZE 100
using namespace std;
int c[SIZE][SIZE];
int n,r;
int calculate_combination(int n,int r);
int main()
{
    cout<<"Enter n: ";
    cin>>n;
    cout<<"Enter r: ";
    cin>>r;
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            c[i][j]=-1;
        }
    }
    cout<<calculate_combination(n,r)<<endl;
    return 0;
}
int calculate_combination(int n,int r)
{
    if(c[n][r]!=-1)
    {
        return c[n][r];
    }
    else if(r==1)
    {
        c[n][r]=n;
    }
    else if(r==n || r==0)
    {
        c[n][r]=1;
    }
    else 
    {
        c[n][r]=calculate_combination(n-1,r-1)+calculate_combination(n-1,r);
    }
    return c[n][r];
}