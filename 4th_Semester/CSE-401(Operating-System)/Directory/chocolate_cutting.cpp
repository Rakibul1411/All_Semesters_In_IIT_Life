#include<bits/stdc++.h>
using namespace std;
int prices[1000][1000];

int cutPrice[1000][1000];

int revenue(int m,int n){
    if(cutPrice[m][n]!= -1)return cutPrice[m][n];
    if(n==0 || m==0)return 0;
    int profit = -1;
    for(int row=1; row<=m; row++){
        for(int col=1; col<=n; col++){
           profit = max(max(prices[row][n] + revenue(m-row,n),profit),max(profit,prices[m][col]+revenue(m,n-col)));
         }
    }
    cutPrice[m][n] = profit;
    return cutPrice[m][n];
}

int main(){
    memset(cutPrice,-1,sizeof(cutPrice));
    int n,m;
    cout << "Ente m and n: ";
    cin >> m >> n;
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            cin >> prices[i][j];
        }
    }
    cout << revenue(2,3) << endl;
}