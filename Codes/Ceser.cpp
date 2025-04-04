#include <bits/stdc++.h>
using namespace std;

void ceaser(string &word)
{
    string result = word;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            result[i] = ((word[i] - 'a') + 3) % 26 + 'a';
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            result[i] = ((word[i] - 'A') + 3) % 26 + 'A';
        }
        else
        {
            result[i] = word[i];
        }
    }
    word = result;
}

void decrypt(string &word)
{
    string result = word;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            result[i] = (word[i] - 'a' - 3 + 26) % 26 + 'a';
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            result[i] = (word[i] - 'A' - 3 + 26) % 26 + 'A';
        }
        else
        {
            result[i] = word[i];
        }
    }
    word = result;
}
int main()
{
    string word;
    cout << "Enter word to encrypt: ";
    cin >> word;

    cout << "Encrypted word: ";
    ceaser(word);
    cout << word << endl;
    cout << "Decrypted word: ";
    decrypt(word);
    cout << word << endl;
    return 0;
}