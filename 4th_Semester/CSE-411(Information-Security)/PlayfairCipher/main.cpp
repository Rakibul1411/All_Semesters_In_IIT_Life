#include <iostream>
#include <string>
using namespace std;

void convertToLowercase(string& text)
{
    for (char &c : text) {
        if (c >= 'A' && c <= 'Z')
            c += 32;
    }
}

int removeSpaces(string& text)
{
    int count = 0;
    for (char &c : text) {
        if (c != ' ')
            text[count++] = c;
    }
    text.resize(count);
    return count;
}

void generateKeyTable(const string& key, string& keyTable)
{
    int i, j, k, flag = 0;
    int charCount[26] = { 0 };

    for (i = 0; i < key.size(); i++) {
        if (key[i] != 'j')
            charCount[key[i] - 'a'] = 2;
    }

    charCount['j' - 'a'] = 1;

    i = 0;
    j = 0;

    for (k = 0; k < key.size(); k++) {
        if (charCount[key[k] - 'a'] == 2) {
            charCount[key[k] - 'a'] -= 1;
            keyTable.push_back(key[k]);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    for (k = 0; k < 26; k++) {
        if (charCount[k] == 0) {
            keyTable.push_back(static_cast<char>(k + 'a'));
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

void findPositions(const string& keyTable, char a, char b, int positions[])
{
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (keyTable[i * 5 + j] == a) {
                positions[0] = i;
                positions[1] = j;
            }
            else if (keyTable[i * 5 + j] == b) {
                positions[2] = i;
                positions[3] = j;
            }
        }
    }
}

int mod5(int a) { return (a % 5); }

void adjustLength(string& text)
{
    if (text.size() % 2 != 0) {
        text.push_back('z');
    }
}

void performEncryption(string& text, const string& keyTable)
{
    int i, positions[4];

    for (i = 0; i < text.size(); i += 2) {
        findPositions(keyTable, text[i], text[i + 1], positions);

        if (positions[0] == positions[2]) {
            text[i] = keyTable[positions[0] * 5 + mod5(positions[1] + 1)];
            text[i + 1] = keyTable[positions[0] * 5 + mod5(positions[3] + 1)];
        }
        else if (positions[1] == positions[3]) {
            text[i] = keyTable[mod5(positions[0] + 1) * 5 + positions[1]];
            text[i + 1] = keyTable[mod5(positions[2] + 1) * 5 + positions[1]];
        }
        else {
            text[i] = keyTable[positions[0] * 5 + positions[3]];
            text[i + 1] = keyTable[positions[2] * 5 + positions[1]];
        }
    }
}

void playfairCipherEncrypt(string& text, const string& key)
{
    string keyTable;

    string lowercaseKey = key;
    convertToLowercase(lowercaseKey);
    removeSpaces(lowercaseKey);

    string lowercaseText = text;
    convertToLowercase(lowercaseText);
    removeSpaces(lowercaseText);

    adjustLength(lowercaseText);

    generateKeyTable(lowercaseKey, keyTable);

    performEncryption(lowercaseText, keyTable);

    text = lowercaseText;
}

int main()
{
    string text, key;

    cout << "Enter the Key text: ";
    getline(cin, key);

    cout << "Enter the plain text: ";
    getline(cin, text);

    playfairCipherEncrypt(text, key);

    cout << "Cipher text: " << text << "\n";

    return 0;
}
