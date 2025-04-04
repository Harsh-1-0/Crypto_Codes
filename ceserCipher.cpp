#include <iostream>
using namespace std;

void ceaserEncryption(string &word)
{
    string result = "";
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            result += (char)((word[i] - 'a' + 3) % 26 + 'a');
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            result += (char)(word[i] - 'A' + 3) % 26 + 'A';
        }
        else
        {
            result += word[i];
        }
    }
    word = result;
}

void cesearDecryption(string &word)
{
    string result = "";
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            result += (char)(word[i] - 'a' - 3 + 26) % 26 + 'a';
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            result += (char)(word[i] - 'A' - 3 + 26) % 26 + 'A';
        }
        else
        {
            result += word[i];
        }
    }

    word = result;
}

int main()
{
    string word;
    cin >> word;
    ceaserEncryption(word);
    cout << word << endl;
    cesearDecryption(word);
    cout << word << endl;
    return 0;
}