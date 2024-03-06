#include<stdio.h>
#define max 100
int graph[max][max];
typedef struct edge 
{
    int u;
    int v;
    int w;
}edge;
typedef struct list
{
    edge value[max];
    int n;
}list;
list edge_list;
list span_list;
int belonging_parent[max];
int find_parent(int n,int u)
{
    return belonging_parent[u];
}
void change_belonging_parent(int n,int u,int v)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(belonging_parent[i]==v)
        {
            belonging_parent[i]=u;
        }
    }
}
void kruskal(int n)
{
    int i,j;
    edge_list.n=0;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            //printf("%d ",graph[i][j]);
            if(graph[i][j]!=0)
            {
                edge_list.value[edge_list.n].u=i;
                edge_list.value[edge_list.n].v=j;
                edge_list.value[edge_list.n].w=graph[i][j];
                edge_list.n++;
                //printf("%d ",edge_list.value[edge_list.n-1].w);
            }
        }
    }
    //printf("%d\n",edge_list.n);
    for(i=0;i<n;i++)
    {
        belonging_parent[i]=i;
    }
    for(i=0;i<edge_list.n-1;i++)
    {
        for(j=0;j<edge_list.n-i-1;j++)
        {
            if(edge_list.value[j].w>edge_list.value[j+1].w)
            {
                edge temp=edge_list.value[j];
                edge_list.value[j]=edge_list.value[j+1];
                edge_list.value[j+1]=temp;
            }
        }
    }
   // printf("%d\n",edge_list.n);
   //printf("%d \n",edge_list.value[2].w);
    span_list.n=0;
    for(i=0;i<edge_list.n;i++)
    {
       
        int u=find_parent(n,edge_list.value[i].u);
        int v=find_parent(n,edge_list.value[i].v);
        if(u!=v)
        {
            span_list.value[span_list.n]=edge_list.value[i];
            change_belonging_parent(n,u,v);
            span_list.n++;
        }
 
    }
   // printf("%d\n",span_list.n);
   int cost=0;
   for(i=0;i<span_list.n;i++)
   {
       printf("%d-%d: %d\n",span_list.value[i].u,span_list.value[i].v,span_list.value[i].w);
       cost=cost+span_list.value[i].w;
   }
   printf("Cost is: %d\n",cost);

}

int main()
{
    int n;
    freopen("kruskal.txt","r",stdin);
    scanf("%d",&n);
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&graph[i][j]);
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",graph[i][j]);
        }
        printf("\n");
    }
    kruskal(n);
}