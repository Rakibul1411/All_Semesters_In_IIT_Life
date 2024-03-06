#include<bits/stdc++.h>
using namespace std;
int main()
{
    int variable,constraints;
    cout<<"Enter the number of variable: ";
    cin>>variable;
    cout<<"Enter the number of constraints: ";
    cin>>constraints;
    double matrix[constraints+1][variable+constraints+2];
    cout<<"Enter the coefficient of variable and constraints: "<<endl;
    int i,j;
    for(i=0;i<constraints+1;i++)
    {
        for(j=0;j<variable+constraints+2;j++)
        {
            cin>>matrix[i][j];
        }
    }
    //int k=3;
    while(1)
    {
        double minimum=5555;
        int pivot_column;
        for(i=0;i<variable+constraints+1;i++)
        {
            if(matrix[0][i]<minimum)
            {
                minimum=matrix[0][i];
                pivot_column=i;
            }
        }
        if(minimum<0)
        {
            double another_minimum=5555;
            int pivot_row;
            for(i=1;i<constraints+1;i++)
            {
                if(matrix[i][variable+constraints+1]/matrix[i][pivot_column]<another_minimum && matrix[i][variable+constraints+1]/matrix[i][pivot_column]>0)
                {
                    another_minimum=matrix[i][variable+constraints+1]/matrix[i][pivot_column];
                    pivot_row=i;
                }
            }
            double pivot=matrix[pivot_row][pivot_column];
            for(i=0;i<variable+constraints+2;i++)
            {
                matrix[pivot_row][i]/=pivot;
            }
            for(i=0;i<constraints+1;i++)
            {
                if(i!=pivot_row)
                {
                    double get_minimum=matrix[i][pivot_column];
                   // cout<<get_minimum<<endl;
                    for(j=0;j<variable+constraints+2;j++)
                    {
                        matrix[i][j]-=get_minimum*matrix[pivot_row][j];
                    }
                }
            }
        }
        else 
        {
            break;
        }
    }
    for(i=0;i<constraints+1;i++)
    {
        for(j=0;j<variable+constraints+2;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}