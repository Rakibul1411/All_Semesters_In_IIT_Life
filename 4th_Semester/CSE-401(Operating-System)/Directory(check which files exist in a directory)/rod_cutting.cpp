#include<bits/stdc++.h>
#define SIZE 1000
using namespace std;
int memory[SIZE];
int solution[SIZE];
int len;
int length[]={1,2,3,4,5,6,7,8,9,10};
int price[]={1,5,8,9,10,12,17,20,23,30};
int revenue (int n,int highest_len);
int main()
{
    cout<<"Enter the length of rod: ";
    cin>>len;
    int i;
    for(i=0;i<SIZE;i++)
    {
        memory[i]=-1;
    }
    int highest_size=sizeof(length)/sizeof(length[0]);
    cout<<revenue(len,highest_size)<<endl;
    while(len>0)
    {
        cout<<solution[len]<<" ";
        len=len-solution[len];
    }
    cout<<endl;
}
int revenue(int n,int highest_len)
{
    int x,q;
    if(memory[n]>=0)
    {
        return memory[n];
    }
    else if(n==0)
    {
        memory[n]=0;
    }
    else 
    {
        q=-1;
        if(n<highest_len)
        {
            x=n;
        }
        else 
        {
            x=highest_len;
        }
        for(int i=1;i<=x;i++)
        {
            int p =price[i-1]+revenue(n-i,highest_len);
            if(p>=q)
            {
                solution[n]=i;
                q=p;
            }
        }
        memory[n]=q;
    }
    return memory[n];
}
// for(i=1;i<=10;i++)
//         {
//             //comment kora tao hbe
//              if(i<=n)
//               {
//                    int p;
//                    p =price[i-1]+memoized_rodCutting(price,n-i);
//                   //q=max(q,price[i-1]+memoized_rodCutting(memory,price,n-i));
//                   if(p>=q)
//                   {
//                       solution[n]=i;
//                       q=p;
//                   }

//               }
//         }