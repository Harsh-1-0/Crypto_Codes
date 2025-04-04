#include <iostream>
#include <vector>

using namespace std;

void printArray(const vector<int> &arr)
{
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
}

void initialization(int n, vector<int> &key, vector<int> &stateVector)
{
    stateVector.clear(); // Reset state vector before initialization
    vector<int> newKey;
    for (int i = 0; i < n; i++)
    {
        stateVector.push_back(i);
        newKey.push_back(key[i % key.size()]);
    }
    key = newKey;
}

void permutation(int n, vector<int> &key, vector<int> &S)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        j = (j + S[i] + key[i]) % n;
        swap(S[i], S[j]);
    }
}

vector<int> pseudoRandomG(int n, int m, vector<int> &S, vector<int> &pt)
{
    vector<int> ans(n, 0);
    int j = 0, i = 0, loop = 0;

    while (loop < n)
    {
        i = (i + 1) % m;
        j = (j + S[i]) % m;
        swap(S[i], S[j]);
        int k = S[(S[i] + S[j]) % m];
        ans[loop] = pt[loop] ^ k;
        loop++;
    }
    return ans;
}

int main()
{
    int n = 4, stateS = 8;
    vector<int> pt, key, stateVector;
    int a;

    cout << "Enter Plain Text (" << n << " values): " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        pt.push_back(a);
    }

    cout << "Enter Key (" << n << " values): " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        key.push_back(a);
    }

    // Save the original key for reinitialization
    vector<int> originalKey = key;

    // Encryption Process
    initialization(stateS, key, stateVector);
    permutation(stateS, key, stateVector);
    vector<int> ct = pseudoRandomG(n, stateS, stateVector, pt);

    cout << "Encrypted Cipher Text: ";
    printArray(ct);

    // Reset key and stateVector for decryption
    key = originalKey;
    initialization(stateS, key, stateVector);
    permutation(stateS, key, stateVector);

    vector<int> decryptedPt = pseudoRandomG(n, stateS, stateVector, ct);

    cout << "Decrypted Plain Text: ";
    printArray(decryptedPt);

    return 0;
}
