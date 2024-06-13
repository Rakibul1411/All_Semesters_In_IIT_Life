#include<iostream>
#define n 5
using namespace std;
int w[n][n],dist[n],previous[n];
int flag[n];
void initialize_single_source(int source);
void relax(int u,int v);
void dijkstra(int s);
int extract_min();
void printgraph();
void printpath(int destination);
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
    //printgraph();
    dijkstra(0);
    for(i=0;i<n;i++)
    {
        cout<<dist[i]<<" ";
    }
    cout<<endl;
    printpath(4);
}
void initialize_single_source(int source)
{
    int i;
    for(i=0;i<n;i++)
    {
        dist[i]=5555;
        previous[i]=-1;
    }
    dist[source]=0;
}
void relax(int u,int v)
{
    if(dist[v]>dist[u]+w[u][v])
    {
        dist[v]=dist[u]+w[u][v];
        previous[v]=u;
    }
}
void dijkstra(int s)
{
    initialize_single_source(s);
    for(int i=0; i<n; i++){
        flag[i] = 1;
    }
    int queueSize = n;
    while(queueSize--)
    {
        int u = extract_min();
        flag[u]=0;
        for (int v = 0; v < n; v++)
        {
            if(w[u][v] > 0)
            {
                relax(u, v);
            }
        }
    }
}
int extract_min(){
    int m =5555, index=-1;

    for(int i=0; i<n; i++){
        if(flag[i] && m > dist[i]){
            m = dist[i];
            index = i;
        }
    }
    return index;
}
void printgraph()
{
    int u, v;
    for (u = 0; u < n; u++ )
    {
        for(v = 0; v < n; v++)
        {
            cout<<w[u][v]<<" ";
        }
        cout<<endl;
    }
}
void printpath(int destination)
{
    if(destination==-1) return;
    printpath(previous[destination]);
    cout<<destination<<"->";
}
