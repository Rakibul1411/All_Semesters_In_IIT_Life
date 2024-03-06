#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main() {
    int n, sum_odd=0, sum_even=0;
    cout<<"Enter the number:";
    cin>>n;

    int pid = fork();
    if(pid < 0){
        cout<<"Fork Creation Fail";
        exit(0);
    } else if( pid == 0){
        for (int i = 1; i <= n; ++i) {
            if(i%2 != 0){
                sum_odd += i;
            }
        }
        cout <<"Sum of Odd term = "<<sum_odd<<endl;
    }
    else {
        for (int i = 1; i <= n; ++i) {
            if (i % 2 == 0) {
                sum_even += i;
            }
        }
        cout <<"Sum of Even term = "<<sum_even<<endl;
    }

    return 0;
}
