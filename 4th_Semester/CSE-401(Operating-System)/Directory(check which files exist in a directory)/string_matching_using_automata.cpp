#include<bits/stdc++.h>
using namespace std;
string pattern;
int transition[100][100];
char alpha[100];
int n=0;
void create_transition_function();
void finding_automata_matching(string text);
int main(){
    string text;
    cout<<"Enter the input text: ";
    cin>>text;
    cout<<"Enter the pattern for string matching: ";
    cin>>pattern;
    int i,j;
    for(i=0;text[i]!='\0';i++)
    {
        for(j=0;j<n;j++)
        {
            if(text[i]==alpha[j])
            {
                break;
            }
        }
        if(j==n)
        {
            alpha[n]=text[i];
            n++;
        }
    }
create_transition_function();
finding_automata_matching(text);
}
void create_transition_function(){
    int m = pattern.size();
    //int lenalpha = alpha.size();
    int q,i,j,k;
    for(q=0;q<=m;q++){
        for(j=0;j<n;j++){
            k=1+min(m,q+1);
        while(1){
            k=k-1;
            if(k==0)break;
            string pref;
            string suff;
            pref=pattern.substr(0,k);
            suff=pattern.substr(0,q);
            suff+=alpha[j];
            string check = suff.substr(suff.size()-k);
            if(pref==check)break;
        }
        transition[q][alpha[j]-'a']=k;
        }
    }
    cout<<"Transition Function:"<<endl;
    for(i=0;i<m+1;i++){
        for(j=0;j<n;j++){
            cout<<transition[i][j]<<" ";
        }
        cout<<endl;
    }
}
void finding_automata_matching(string text){
    int x = text.size();
    int q=0,i,m,s,count=0;
    m=pattern.size();
    for(i=0;i<x;i++){
        q=transition[q][text[i]-'a'];
        if(q==m){
            s=i-m+1;
            cout<<"Pattern occurs with shift "<<s<<endl;
            count++;
        }
    }
    cout<<"Total matched substr : "<<count<<endl;
}