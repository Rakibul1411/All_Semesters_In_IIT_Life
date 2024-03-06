#include<bits/stdc++.h>
#define Size 100
using namespace std;
string x,y;
int c[Size][Size];
char b[Size][Size];
void print_edit(int m,int n);
int main()
{
    cout<<"Enter the string that you want to convert: ";
    cin>>x;
    cout<<"Enter the string that you desire: ";
    cin>>y;
    int i,j;
    for(i=0;i<=x.size();i++)
        {
            c[i][0]=i;
            b[i][0]='D';
        }
    for(j=0;j<=y.size();j++)
        {
            c[0][j]=j;
            b[0][j]='I';
        }
    for(i=1;i<=x.size();i++)
    {
        for(j=1;j<=y.size();j++)
        {
            if(x[i-1]==y[j-1])
            {
                c[i][j]=c[i-1][j-1];
                b[i][j]='N';
            }
            else
            {
                if(c[i-1][j-1]<=c[i-1][j] && c[i-1][j-1]<=c[i][j-1])
                    {
                        c[i][j]=c[i-1][j-1]+1;
                        b[i][j]='S';
                    }
                else if(c[i-1][j]<=c[i-1][j-1] && c[i-1][j]<=c[i][j-1])
                    {
                        c[i][j]=c[i-1][j]+1;
                        b[i][j]='D';
                    }
                else
                   {
                        c[i][j]=c[i][j-1]+1;
                        b[i][j]='I';
                   }
            }
        }
    }
    for(i=0;i<=x.size();i++)
    {
        for(j=0;j<=y.size();j++)
        {
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<c[x.size()][y.size()]<<endl;
     for(i=0;i<=x.size();i++)
    {
        for(j=0;j<=y.size();j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    print_edit(x.size(),y.size());   
}
void print_edit(int m,int n)
{
    if(m==0 && n==0)
    {
        return;
    }
    else if(b[m][n]=='N')
    {
        print_edit(m-1,n-1);
    }
    else if(b[m][n]=='D')
    {
        print_edit(m-1,n);
        cout<<"Delete "<<x[m-1]<<endl;
    }
    else if(b[m][n]=='S')
    {
        print_edit(m-1,n-1);
        cout<<"Substitute "<<x[m-1]<<" by "<<y[n-1]<<endl;
    }
    else 
    {
        print_edit(m,n-1);
        cout<<"Insert "<<y[n-1]<<endl;
    }
}
// while(m>0 && n>0)
//     {
//         if(b[m][n]=='N')
//         {
//             m--;
//             n--;
//         }
//         else if(b[m][n]=='S')
//         {
//             printf("Substitute %c of x by %c of y\n",x[m-1],y[n-1]);
//             m--;
//             n--;
//         }
//         else if(b[m][n]='D')
//         {
//             printf("delete %c from x\n",x[m-1]);
//             m--;
//         }
//         else
//         {
//             printf("insert %c in x\n",y[n-1]);
//             n--;
//         }
//     }
//     while(m>0)
//     {
//         printf("delete %c\n",x[m-1]);
//         m--;
//     }
//     while(n>0)
//     {
//         printf("insert %c\n",y[n-1]);
//         n--;
//     }