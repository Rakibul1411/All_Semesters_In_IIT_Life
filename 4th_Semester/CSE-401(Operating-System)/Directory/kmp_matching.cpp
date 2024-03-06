#include<bits/stdc++.h>
using namespace std;
int main()
{
    string text,pattern;
    cout<<"Enter the text: ";
    cin>>text;
    cout<<"Enter the pattern: ";
    cin>>pattern;
    int m=pattern.size();
    int n=text.size();
    int prefix_function[m];
    prefix_function[0]=0;
    int k=0;
    int i;
    //prefix function generate.ekhane indexing 0 based tai pattern[k+1] lekha hoy nai.
    for(i=1;i<m;i++)
    {
        while(k>0 && pattern[k]!=pattern[i])
        {
            k=prefix_function[k-1];
        }
        if(pattern[k]==pattern[i])
        {
            k=k+1;
        }
        prefix_function[i]=k;
    }
    for(i=0;i<m;i++)
    {
        cout<<prefix_function[i]<<" ";
    }
    cout<<endl;
    //kmp matecher 
    int j=0,count=0;
    for(i=0;i<n;i++)
    {
        while(j>0 && text[i]!=pattern[j])
        {
            j=prefix_function[j-1];
        }
        if(text[i]==pattern[j])
        {
            j=j+1;
        }
        if(j==m)
        {
            count++;
            j=prefix_function[j-1];
            cout<<"pattern matches with shift "<<i-m+1<<endl;
        }
    }
    cout<<"Total matched pattern: ";
    cout<<count<<endl;
}