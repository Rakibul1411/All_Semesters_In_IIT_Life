#include<stdio.h>
#define size 1000
int n;
int capacity_graph[size][size],flow[size][size],predecessor[size];
int head, tail;
int queue[size];
int visited[size];

void enqueue(int x) {
  queue[tail] = x;
  tail++;
}

int dequeue() {
  int x = queue[head];
  head++;
  return x;
}
int bfs(int source,int sink)
{
    int u, v;
  for (u = 0; u < n+2; u++) {
    visited[u] =0;
  }
  head = tail = 0;
  enqueue(source);
  visited[source]=1;
  predecessor[source] = -1;
  while (head != tail) 
  {
    u = dequeue();
    for (v = 0; v < n+2; v++) 
    {
      if (visited[v] == 0 && capacity_graph[u][v] - flow[u][v] > 0) 
      {
        enqueue(v);
        predecessor[v] = u;
        visited[v]=1;
        if(v==sink)
        {
            return 1;
        }
      }
    }
  }
  return 0;
}
int minimum(int a,int b)
{
    if(a>b) return b;
    else return a;
}
int fordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 0; i < n+2; i++)
   {
    for (j = 0; j < n+2; j++) 
    {
      flow[i][j] = 0;
    }
  }
  while (bfs(source, sink))
   {
    int increment =55555;
    for (u =sink; predecessor[u] >= 0; u = predecessor[u]) 
    {
      increment = minimum(increment, capacity_graph[predecessor[u]][u] - flow[predecessor[u]][u]);
    }
    for (u =sink; predecessor[u] >= 0; u = predecessor[u]) 
    {
      flow[predecessor[u]][u] += increment;
      //capacity_graph[predecessor[u]][u]-=increment;
    }
    max_flow += increment;
  }
  return max_flow;
}
int main()
{
    //freopen("fulkersion.txt","r",stdin);
    printf("Enter the number of vertices: ");
    scanf("%d",&n);
    printf("Enter the capacity of the garph: \n");
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&capacity_graph[i][j]);
        }
    }
    printf("Enter the number of multiple sources: ");
    int s;
    scanf("%d",&s);
    int source[s];
    for(i=0;i<s;i++)
    {
        scanf("%d",&source[i]);
    }
    printf("Enter the number of sink: ");
    int t;
    scanf("%d",&t);
    int sink[t];
    for(i=0;i<t;i++)
    {
        scanf("%d",&sink[i]);
    }
    for(i=0;i<n+2;i++)
    {
        for(j=0;j<n+2;j++)
        {
            if(i>=n)
            {
                capacity_graph[i][j]=0;
            }
        }
    }
    int super_source=n;
    int super_sink=n+1;
    for(i=0;i<s;i++)
    {
        capacity_graph[super_source][source[i]]=55555;
    }
    for(i=0;i<t;i++)
    {
        capacity_graph[sink[i]][super_sink]=55555;
    }  
    printf("Maximum flow: %d\n",fordFulkerson(super_source,super_sink));
}