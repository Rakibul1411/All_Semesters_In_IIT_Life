#include<bits/stdc++.h>
using namespace std;
int len[1000];
int len_prime[1000];
int previous[1000];
int input[1000];
void printlis(int index);
int main()
{
    cout<<"Enter the number of input: ";
    int n,i;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>input[i];
    }
    len[0]=-1;
    len_prime[0]=-1;
    previous[0]=-1;
    int length=0;
    for(i=1;i<=n;i++)
    {
        if(len[length]<input[i])
        {
            length=length+1;
            len[length]=input[i];
            len_prime[length]=i;
            previous[i]=len_prime[length-1];
        }
        else
        {
            int s=0;
            int h=length;
            while(s<h)
            {
                int m=(s+h)/2;
                if(len[m]<input[i])
                {
                    s=m+1;
                }
                else
                {
                    h=m;
                }
            }
            len[s]=input[i];
            len_prime[s]=i;
            previous[i]=len_prime[s-1];
        }
    }
    cout<<length<<endl;
    printlis(len_prime[length]);
}
void printlis(int index)
{
    if(index==-1) return;
    printlis(previous[index]);
    printf("%d ",input[index]);
}