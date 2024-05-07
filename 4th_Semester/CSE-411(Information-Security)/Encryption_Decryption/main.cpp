#include <iostream>
#include <string>
using namespace std;
int main() {
    cout<<"Enter the String: "<<endl;
    string input;
    getline(cin, input);
    cout<<"Enter the key: "<<endl;
    int key;
    cin>> key;

    string encrypted_text, decrypted_text;
    for (int i = 0; i < input.size(); ++i) {

        if(input[i] ==' '){
            encrypted_text += input[i];
        }
        else{
            int mod = (input[i]%97+key)%26;
            char pos = 'a'+mod;
            encrypted_text += pos;
        }

    }

    cout << "Encryption text is: " << encrypted_text << endl << endl;

    for (int i = 0; i < encrypted_text.size(); ++i) {
        if (encrypted_text[i] == ' '){
            decrypted_text += encrypted_text[i];
        }

        else{
            int value = (encrypted_text[i]%97 - key);

            if(value < 0){
                char add = 'z'+value+1;
                decrypted_text += add;
            }
            else{
                char next = 'a'+value;
                decrypted_text += next;
            }
        }

    }

    cout << "Decryption text is: " << decrypted_text << endl;

    return 0;
}
