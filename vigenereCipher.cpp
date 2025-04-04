#include <iostream>
#include <string>
using namespace std;

void vigenereCipherEncryption(string &word, string key)
{
    for (int i = 0; i < word.length(); i++)
    {
        int keyVal;
        if (key[i % key.length()] >= 'a' && key[i % key.length()] <= 'z')
        {
            keyVal = key[i % key.length()] - 'a';
        }
        else
        {
            keyVal = key[i % key.length()] - 'A';
        }
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            word[i] = (char)((word[i] - 'a' + keyVal) % 26 + 'a');
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            word[i] = (char)((word[i] - 'A' + keyVal) % 26 + 'A');
        }
    }
}

void vigenereCipherDecryption(string &word, string key)
{
    for (int i = 0; i < word.length(); i++)
    {
        int keyVal;
        if (key[i % key.length()] >= 'a' && key[i % key.length()] <= 'z')
        {
            keyVal = key[i % key.length()] - 'a';
        }
        else
        {
            keyVal = key[i % key.length()] - 'A';
        }
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            word[i] = (char)((((word[i] - 'a' - keyVal) + 26) % 26) + 'a');
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            word[i] = (char)((((word[i] - 'A' - keyVal) + 26) % 26) + 'A');
        }
    }
}

int main()
{
    string word, key;
    cin >> word >> key;
    string temp = "";
    for (int i = 0; i < word.length(); i++)
    {
        if (isalpha(word[i]))
        {
            temp += word[i];
        }
    }
    cout << temp << endl;
    vigenereCipherEncryption(temp, key);
    int j = 0;
    for (int i = 0; i < word.length(); i++)
    {
        if (isalpha(word[i]))
        {
            word[i] = temp[j];
            j++;
        }
    }
    cout << word << endl;
    vigenereCipherDecryption(temp, key);
    j = 0;
    for (int i = 0; i < word.length(); i++)
    {
        if (isalpha(word[i]))
        {
            word[i] = temp[j];
            j++;
        }
    }
    cout << word << endl;

    return 0;
}