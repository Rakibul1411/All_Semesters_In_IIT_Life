#include<bits/stdc++.h>
using namespace std;
void print_interval(int prev[],int index,int input[]);
int main()
{
    printf("Enter the number of input: ");
    int n;
    cin>>n;
    int input[n];
    int i;
    for(i=0;i<n;i++)
    {
        cin>>input[i];
    }
    int sum[n+1];
    int prev[n+1];
    sum[0]=0;
    prev[0]=0;
    for(i=0;i<n;i++)
    {
        sum[i+1]=sum[i]+input[i];
        prev[i+1]=i;
        if(input[i]>sum[i+1])
        {
            sum[i+1]=input[i];
            prev[i+1]=0;
        }
    }
    for(i=0;i<n+1;i++)
    {
        cout<<prev[i]<<" ";
    }
    cout<<endl;
    int max=INT_MIN;
    int get_max_index;
    for(i=0;i<n+1;i++)
    {
        if(max<sum[i])
        {
            max=sum[i];
            get_max_index=i;
        }
    }
    print_interval(prev,get_max_index,input);
    cout<<endl;
}
void print_interval(int prev[],int index,int input[])
{
    if(prev[index]>0)
        print_interval(prev,prev[index],input);
        cout<<input[index-1]<<" ";
}