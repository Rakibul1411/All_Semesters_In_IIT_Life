#include<stdio.h>
#define size 100
int n;
int index=0;
int printarray[size];
int w[size][size],distance[size],prev[size];
int flag[size];
void initialize_single_source(int source)
{
    int i;
    for(i=0;i<n;i++)
    {
        distance[i]=5555;
        prev[i]=-1;
    }
    distance[source]=0;
}
void relax(int u,int v)
{
    if(distance[v]>w[u][v])
    {
        distance[v]=w[u][v];
        prev[v]=u;
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
        printarray[index]=u;
        index++;       
        flag[u]=0;
        for (int v =0; v < n; v++)
        {
            if(w[u][v] > 0)
            {
                relax(u, v);
                w[v][u]=0;
            }
        }
    }
}
int extract_min(){
    int m =5555, index=-1;

    for(int i=0; i<n; i++){
        if(flag[i] && m > distance[i]){
            m = distance[i];
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
            printf("%d ",w[u][v]);
        }
        printf("\n");
    }
}
void printpath()
{
    // int j;
    // for(j=0;j<index;j++)
    // {
    //     printf("%d ",printarray[j]);
    // }
    // printf("\n");
    // for(j=0;j<index;j++)
    // {
    //     printf("%d ",prev[j]);
    // }
    int i;
    int cost=0;
    for(i=1;i<index;i++)
    {
        printf("%d-%d= %d\n",prev[printarray[i]],printarray[i],w[prev[printarray[i]]][printarray[i]]);
        cost+=w[prev[printarray[i]]][printarray[i]];
    }
    printf("Cost=%d\n",cost);
}
int main()
{
    freopen("kruskal.txt","r",stdin);
    scanf("%d",&n);
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&w[i][j]);
        }
    }
    printgraph();
    dijkstra(0);
    printf("\n");
    printpath();
}