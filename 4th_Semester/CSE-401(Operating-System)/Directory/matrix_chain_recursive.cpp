#include<bits/stdc++.h>
#define Size 100
using namespace std;
int m[Size][Size];
int s[Size][Size];
int recursive_matrix_chain(int p[],int i,int j);
void printParentheses(int i, int j);
int main()
{
    int n;
    cout<<"Enter the number of matrix: ";
    cin>>n;
    int dimensions[n + 1];
    cout<<"Enter the dimensions: "<<endl;
    for (int i = 0; i <= n; i++) 
    {
        scanf("%d", &dimensions[i]);
    }
    cout<<recursive_matrix_chain(dimensions,1,n)<<endl;
    printParentheses(1,n);
}
int recursive_matrix_chain(int p[],int i,int j)
{
    if(i==j)
    {
        m[i][j]=0;
        return m[i][j];
    }
    int k,q;
    m[i][j]=INT_MAX;
    for(k=i;k<j;k++)
    {
        q=recursive_matrix_chain(p,i,k)+recursive_matrix_chain(p,k+1,j)+p[i-1]*p[k]*p[j];
        if(q<m[i][j])
        {
            m[i][j]=q;
            s[i][j]=k;
        }
    }
    return m[i][j];
}
void printParentheses(int i, int j) 
{
    if (i == j) {
        cout<<"A"<<i;
        return;
    }
    printf("(");
    printParentheses(i, s[i][j]);
    printParentheses(s[i][j] + 1, j);
    printf(")");
}
