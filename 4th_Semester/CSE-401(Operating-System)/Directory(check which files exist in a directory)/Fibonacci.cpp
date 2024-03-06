#include<bits/stdc++.h>
#define size 100
using namespace std;
int fibonacci_number[size];
int nsu_number[size];
int calculate_fibonacci_number(int n);
int calculate_nsu_number(int n);
int number;
int main()
{
    cout<<"Enter the number: ";
    cin>>number;
    int i,j;
    for(i=0;i<size;i++)
    {
        fibonacci_number[i]=-1;
        nsu_number[i]=-1;
    }
    cout<<calculate_fibonacci_number(number)<<endl;
    cout<<calculate_nsu_number(number)<<endl;
}
int calculate_fibonacci_number(int n)
{
    if(fibonacci_number[n]>=0)
    {
        return fibonacci_number[n];
    }
    else if(n<=1)
    {
        fibonacci_number[n]=n;
    }
    else 
    {
        fibonacci_number[n]=calculate_fibonacci_number(n-1)+calculate_fibonacci_number(n-2);
    }
    return fibonacci_number[n];
}
int calculate_nsu_number(int n)
{
    if(nsu_number[n]>=0)
    {
        return nsu_number[n];
    }
    else if(n<=2)
    {
        nsu_number[n]=n;
    }
    else 
    {
        nsu_number[n]=calculate_nsu_number(n-1)+calculate_nsu_number(n-2)+calculate_nsu_number(n-3);
    }
    return nsu_number[n];
}
