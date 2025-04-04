#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

using namespace std;

int determinant2x2(const vector<vector<int>> &matrix)
{
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

int determinant3x3(const vector<vector<int>> &matrix)
{
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

int modularInverse(int num, int mod)
{
    num = num % mod;
    for (int x = 1; x < mod; x++)
    {
        if ((num * x) % mod == 1)
        {
            return x;
        }
    }
    return -1;
}

vector<vector<int>> inverseMatrix2x2(const vector<vector<int>> &matrix, int mod)
{
    int det = determinant2x2(matrix);
    int detInv = modularInverse(det, mod);

    if (detInv == -1)
    {
        throw runtime_error("Matrix is not invertible under mod 26.");
    }

    vector<vector<int>> inverse(2, vector<int>(2));
    inverse[0][0] = matrix[1][1] * detInv % mod;
    inverse[0][1] = -matrix[0][1] * detInv % mod;
    inverse[1][0] = -matrix[1][0] * detInv % mod;
    inverse[1][1] = matrix[0][0] * detInv % mod;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            inverse[i][j] = (inverse[i][j] + mod) % mod;
        }
    }

    return inverse;
}

vector<vector<int>> inverseMatrix3x3(const vector<vector<int>> &matrix, int mod)
{
    int det = determinant3x3(matrix);
    int detInv = modularInverse(det, mod);

    if (detInv == -1)
    {
        throw runtime_error("Matrix is not invertible under mod 26.");
    }

    vector<vector<int>> inverse(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int minorDet = determinant2x2({
                {matrix[(i + 1) % 3][(j + 1) % 3], matrix[(i + 1) % 3][(j + 2) % 3]},
                {matrix[(i + 2) % 3][(j + 1) % 3], matrix[(i + 2) % 3][(j + 2) % 3]},
            });

            inverse[j][i] = ((minorDet * detInv) % mod + mod) % mod;
                }
    }

    for (int i = 0; i < inverse.size(); i++)
    {
        for (int j = 0; j < inverse[i].size(); j++)
        {
            cout << inverse[i][j] << " ";
        }
        cout << endl;
    }

    return inverse;
}

string preprocessText(const string &text)
{
    string result;
    for (char ch : text)
    {
        if (isalpha(ch))
        {
            result.push_back(toupper(ch));
        }
    }
    return result;
}

string padPlaintext(const string &text, int size)
{
    string result = text;
    while (result.length() % size != 0)
    {
        result.push_back('X');
    }
    return result;
}

string matrixMultiply(const vector<vector<int>> &keyMatrix, const string &text, int mod)
{
    int n = keyMatrix.size();
    string result;
    for (size_t i = 0; i < text.length(); i += n)
    {
        vector<int> values(n, 0);
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                values[j] = (values[j] + keyMatrix[j][k] * (text[i + k] - 'A')) % mod;
            }
            result.push_back(values[j] + 'A');
        }
    }
    return result;
}

string hillCipherEncrypt(const string &plaintext, vector<vector<int>> &keyMatrix)
{
    string processedText = preprocessText(plaintext);
    processedText = padPlaintext(processedText, keyMatrix.size());
    return matrixMultiply(keyMatrix, processedText, 26);
}

string hillCipherDecrypt(const string &ciphertext, vector<vector<int>> &keyMatrix)
{
    vector<vector<int>> inverseKeyMatrix;
    if (keyMatrix.size() == 2)
    {
        inverseKeyMatrix = inverseMatrix2x2(keyMatrix, 26);
    }
    else if (keyMatrix.size() == 3)
    {
        inverseKeyMatrix = inverseMatrix3x3(keyMatrix, 26);
    }
    else
    {
        throw runtime_error("Only 2x2 and 3x3 matrices are supported.");
    }
    return matrixMultiply(inverseKeyMatrix, ciphertext, 26);
}

int main()
{
    int size;
    cout << "Enter the size of the key matrix (2 or 3): ";
    cin >> size;

    vector<vector<int>> keyMatrix(size, vector<int>(size));
    cout << "Enter the " << size << "x" << size << " key matrix (row-wise):" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cin >> keyMatrix[i][j];
        }
    }

    string text;
    int choice;
    cout << "Enter the text: ";
    cin.ignore();
    getline(cin, text);

    cout << "Choose an option (1: Encrypt, 2: Decrypt): ";
    cin >> choice;

    try
    {
        if (choice == 1)
        {
            string encryptedText = hillCipherEncrypt(text, keyMatrix);
            cout << "Encrypted text: " << encryptedText << endl;
        }
        else if (choice == 2)
        {
            string decryptedText = hillCipherDecrypt(text, keyMatrix);
            cout << "Decrypted text: " << decryptedText << endl;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
