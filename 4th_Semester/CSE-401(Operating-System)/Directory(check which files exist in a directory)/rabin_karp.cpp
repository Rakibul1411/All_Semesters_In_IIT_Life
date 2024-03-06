#include<bits/stdc++.h>
using namespace std;
int main()
{
    string text;
    string pattern;
    cout<<"Enter the text string: ";
    cin>>text;
    cout<<"Enter the pattern: ";
    cin>>pattern;
    int n=text.size();
    int m=pattern.size();
    int pattern_value=0;
    int text_value[n-m+1];
    int i,offset=1;
    for(i=0;i<m;i++)
    {
        pattern_value=2*pattern_value+pattern[i];
    }
    for(i=0;i<m-1;i++)
    {
        offset=2*offset;
    }
    text_value[0]=0;
    for(i=0;i<m;i++)
    {
        text_value[0]=2*text_value[0]+text[i];
    }
    for(i=1;i<n-m+1;i++)
    {
        text_value[i]=text_value[i-1]-offset*text[i-1];
        text_value[i]=2*text_value[i]+text[m+i-1];
    }
    int count=0;
    for(i=0;i<n-m+1;i++)
    {
        //cout<<text_value[i]<<endl;
        if(pattern_value==text_value[i])
        count++;
    }
    cout<<count<<endl;
}