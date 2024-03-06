#include<bits/stdc++.h>
using namespace std;
char symbol[1000][1000];
void print_item(int num_of_items,int knapsack_weight,int wight_of_items[]);
int main()
{
    cout<<"Enter the number of items: ";
    int num_of_items;
    cin>>num_of_items;
    int value_of_items[num_of_items];
    int weight_of_items[num_of_items];
    int i,j;
    for(i=0;i<num_of_items;i++)
    {
        cout<<"Enter the weight and value of item "<<i+1<<" :";
        cin>>weight_of_items[i]>>value_of_items[i];
    }
    cout<<"Enter the knapsack size : ";
    int knapsack_wight;
    cin>>knapsack_wight;
    int calculate_profit[num_of_items+1][knapsack_wight+1];
    for(i=0;i<num_of_items+1;i++)
    {
        calculate_profit[i][0]=0;
        symbol[i][0]='i';
    }
    for(i=0;i<knapsack_wight+1;i++)
    {
        calculate_profit[0][i]=0;
        symbol[0][i]='i';
    }
    for(i=1;i<num_of_items+1;i++)
    {
        for(j=1;j<knapsack_wight+1;j++)
        {
            if(weight_of_items[i-1]>j)
            {
                calculate_profit[i][j]=calculate_profit[i-1][j];
                symbol[i][j]='u';
            }
            else 
            {
                if(calculate_profit[i-1][j-weight_of_items[i-1]]+value_of_items[i-1]>calculate_profit[i-1][j])
                {
                    calculate_profit[i][j]=calculate_profit[i-1][j-weight_of_items[i-1]]+value_of_items[i-1];
                    symbol[i][j]='t';
                }
                else 
                {
                    calculate_profit[i][j]=calculate_profit[i-1][j];
                    symbol[i][j]='u';
                }
            }
        }
    }
    cout<<calculate_profit[num_of_items][knapsack_wight]<<endl;
    print_item(num_of_items,knapsack_wight,weight_of_items);
    cout<<endl;
}
void print_item(int num_of_items,int knapsack_weight,int weight_of_items[])
{
    if(num_of_items==0)
    {
        return;
    }
    else 
    {
        if(symbol[num_of_items][knapsack_weight]=='u')
        {
            print_item(num_of_items-1,knapsack_weight,weight_of_items);
        }
        else if(symbol[num_of_items][knapsack_weight]=='t')
        {
            print_item(num_of_items-1,knapsack_weight-weight_of_items[num_of_items-1],weight_of_items);
            cout<<num_of_items<<" ";
        }
    }
}