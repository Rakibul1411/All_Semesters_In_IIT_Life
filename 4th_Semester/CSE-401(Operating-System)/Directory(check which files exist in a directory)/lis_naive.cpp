#include<bits/stdc++.h>
#define Size 100
using namespace std;
int length[Size];
int previous[Size];
int input_array[Size];
void print_increasing_subsequence(int max);
int main()
{
    cout<<"Enter the number of input: ";
    int input,i,j;
    cin>>input;
    for(i=1;i<=input;i++)
    {
        cin>>input_array[i];
    }
    length[0]=0;
    previous[0]=0;
    int max_length=0;
    int max_index=0;
    for(i=1;i<=input;i++)
    {
        length[i]=0;
        for(j=1;j<i;j++)
        {
            if(input_array[j]<=input_array[i] && length[j]+1>=length[i])
            {
                length[i]=length[j]+1;
                previous[i]=j;
            }
        }
        if(length[i]>max_length)
        {
            max_length=length[i];
            max_index=i;
        }
    }
    print_increasing_subsequence(max_index);
    cout<<endl;
}
void print_increasing_subsequence(int max)
{
    if(max==0)
    {
        return;
    }
    else 
    {
        print_increasing_subsequence(previous[max]);
        cout<<input_array[max]<<" ";
    }
}