#include <bits/stdc++.h>
#define Size 100
using namespace std;
int m[Size][Size];
int s[Size][Size];
void printParentheses(int i, int j) {
    if (i == j) {
        cout<<"A"<<i;
        return;
    }
    printf("(");
    printParentheses(i, s[i][j]);
    printParentheses(s[i][j] + 1, j);
    printf(")");
}

void matrixChain(int p[], int n) {
    for (int i = 1; i < n; i++) 
    {
        m[i][i] = 0;
    }
    for (int l = 2; l < n; l++) 
    {
        for (int i = 1; i < n - l + 1; i++) 
        {
            int j = i + l - 1;
            m[i][j] =INT_MAX;
            for (int k = i; k <= j - 1; k++) 
            {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) 
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    cout<<"Parenthesized: "<<endl;
    printParentheses(1, n - 1);
    cout<<endl;
    cout<<"cost: "<<m[1][n-1]<<endl;
}

int main() {
    int n;
    cout<<"Enter the number of matrix: ";
    cin>>n;
    int dimensions[n + 1];
    cout<<"Enter the dimensions: "<<endl;
    for (int i = 0; i <= n; i++) 
    {
        scanf("%d", &dimensions[i]);
    }
    matrixChain(dimensions, n + 1);
    return 0;
}
