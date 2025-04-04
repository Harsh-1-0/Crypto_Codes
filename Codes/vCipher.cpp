#include <bits/stdc++.h>
using namespace std;

void vCipher(string &word, string key)
{
    string result = word;
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
            result[i] = (word[i] - 'a' + keyVal) % 26 + 'a';
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            result[i] = (word[i] - 'A' + keyVal) % 26 + 'A';
        }
        else
        {
            result[i] = word[i];
        }
    }
    word = result;
}

void decrypt(string &word, string key)
{
    string result = word;
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
            result[i] = (word[i] - 'a' - keyVal + 26) % 26 + 'a';
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            result[i] = (word[i] - 'A' - keyVal + 26) % 26 + 'A';
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
    string word, key;
    cout << "Enter word to encrypt: ";
    cin >> word;
    cout << "Enter key: ";
    cin >> key;
    string temp = "";
    for (int i = 0; i < word.length(); i++)
    {
        if (isalpha(word[i]))
        {
            temp += word[i];
        }
    }
    vCipher(temp, key);
    int j = 0;
    for (int i = 0; i < word.length(); i++)
    {
        if (isalpha(word[i]))
        {
            word[i] = temp[j++];
        }
    }
    cout << word << endl;
    decrypt(temp, key);
    for (int i = 0; i < word.length(); i++)
    {
        if (isalpha(word[i]))
        {
            word[i] = temp[j++];
        }
    }
    return 0;
}