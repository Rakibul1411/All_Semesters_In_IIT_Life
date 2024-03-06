#include<bits/stdc++.h>
#define n 5
#define inf 5000
using namespace std;
int w[n][n],dist[n],previous[n];
void initialize_single_source(int source);
void printpath(int destination,int store);
int bellmanford(int src);
int main()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>w[i][j];
        }
    }
    if(bellmanford(0))
    {
        for(i=0;i<n;i++)
        {
            cout<<dist[i]<<" ";
        }
        cout<<endl;
        int store=n-1;
        printpath(n-1,store);
    }
    else
    {
        cout<<"Negative cycle exists"<<endl;
    }
    return 0;
}
void initialize_single_source(int source)
{
    int i;
    for(i=0;i<n;i++)
    {
        dist[i]=inf;
        previous[i]=-1;
    }
    dist[source]=0;
}
void relax(int src,int dst)
{
    if(dist[dst]>dist[src]+w[src][dst])
    {
        dist[dst]=dist[src]+w[src][dst];
        previous[dst]=src;
    }
}
void printpath(int destination,int store)
{
    if(destination==-1) 
    {
        return;
    }
    printpath(previous[destination],store);
    if(destination==store)
    {
        cout<<destination<<endl;
    }
    else 
    {
        cout<<destination<<"->";
    }
}
int bellmanford(int src)
{
    initialize_single_source(src);
    int i,j,k;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
            {
                if(w[j][k]!=0)
                {
                    relax(j,k);
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(w[i][j]!=0)
            {
                if(dist[j]>dist[i]+w[i][j])
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
