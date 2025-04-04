#include <bits/stdc++.h>
using namespace std;

void generateKeyMatrix(const string& key, char matrix[5][5]) {
    string processedKey = "";
    vector<bool> used(26, false);

    for (char c : key) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I'; 
            if (!used[c - 'A']) {
                processedKey += c;
                used[c - 'A'] = true;
            }
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; 
        if (!used[c - 'A']) {
            processedKey += c;
            used[c - 'A'] = true;
        }
    }

    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = processedKey[index++];
        }
    }
}

void findPosition(char matrix[5][5], char c, int& row, int& col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string preparePlaintext(const string& plaintext) {
    string processedText = "";
    for (char c : plaintext) {
        if (isalpha(c)) {
            processedText += toupper(c == 'J' ? 'I' : c);
        }
    }

    string result = "";
    for (size_t i = 0; i < processedText.length(); i++) {
        result += processedText[i];
        if (i + 1 < processedText.length() && processedText[i] == processedText[i + 1]) {
            result += 'X'; 
        }
    }
    if (result.length() % 2 != 0) {
        result += 'X'; 
    }
    return result;
}

string encrypt(const string& plaintext, char matrix[5][5]) {
    string ciphertext = "";
    for (size_t i = 0; i < plaintext.length(); i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];
        int row1, col1, row2, col2;
        findPosition(matrix, a, row1, col1);
        findPosition(matrix, b, row2, col2);

        if (row1 == row2) {
            ciphertext += matrix[row1][(col1 + 1) % 5];
            ciphertext += matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext += matrix[(row1 + 1) % 5][col1];
            ciphertext += matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext += matrix[row1][col2];
            ciphertext += matrix[row2][col1];
        }
    }
    return ciphertext;
}

string decrypt(const string& ciphertext, char matrix[5][5]) {
    string plaintext = "";
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];
        int row1, col1, row2, col2;
        findPosition(matrix, a, row1, col1);
        findPosition(matrix, b, row2, col2);

        if (row1 == row2) {
            plaintext += matrix[row1][(col1 + 4) % 5];
            plaintext += matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            plaintext += matrix[(row1 + 4) % 5][col1];
            plaintext += matrix[(row2 + 4) % 5][col2];
        } else {
            plaintext += matrix[row1][col2];
            plaintext += matrix[row2][col1];
        }
    }
    return plaintext;
}

int main() {
    string key;
    cout << "Enter the key: ";
    getline(cin, key);

    char keyMatrix[5][5];
    generateKeyMatrix(key, keyMatrix);

    cout << "\nKey Matrix:" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << keyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    string plaintext;
    cout << "\nEnter the plaintext: ";
    getline(cin, plaintext);

    string preparedPlaintext = preparePlaintext(plaintext);
    cout << "\nPrepared Plaintext: " << preparedPlaintext << endl;

    string ciphertext = encrypt(preparedPlaintext, keyMatrix);
    cout << "Ciphertext: " << ciphertext << endl;

    string decryptedText = decrypt(ciphertext, keyMatrix);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}