#include <iostream>
#include <vector>
#include <iomanip>
#include <cstddef> // For size_t in C++

using namespace std;

enum errorCode
{
    SUCCESS = 0,
    ERROR_AES_UNKNOWN_KEYSIZE,
    ERROR_MEMORY_ALLOCATION_FAILED,
};

// Implementation: S-Box

vector<unsigned char> s_box = {
    // 0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,  // 0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,  // 1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,  // 2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,  // 3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,  // 4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,  // 5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,  // 6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,  // 7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,  // 8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,  // 9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,  // A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,  // B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,  // C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,  // D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,  // E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}; // F

unsigned char getSBoxValue(unsigned char num);
// Implementation: Rotate
void rotate(unsigned char *word);

// Implementation: Rcon
vector<unsigned char> Rcon = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d,
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab,
    0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d,
    0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25,
    0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d,
    0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
    0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a,
    0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02,
    0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
    0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5,
    0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33,
    0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb};

unsigned char getRconValue(unsigned char num);

// Implementation: Key Schedule Core
void core(unsigned char *word, int iteration);

// Implementation: Key Expansion

enum keySize
{
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize, size_t expandedKeySize);

// Implementation: AES Encryption

// Implementation: subBytes
void subBytes(unsigned char *state);
// Implementation: shiftRows
void shiftRows(unsigned char *state);
void shiftRow(unsigned char *state, unsigned char nbr);
// Implementation: addRoundKey
void addRoundKey(unsigned char *state, unsigned char *roundKey);
// Implementation: mixColumns
unsigned char galois_multiplication(unsigned char a, unsigned char b);
void mixColumns(unsigned char *state);
void mixColumn(unsigned char *column);
// Implementation: AES round
void aes_round(unsigned char *state, unsigned char *roundKey);
// Implementation: the main AES body
void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey);
void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
// Implementation: AES encryption
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);

int main(int argc, char *argv[])
{
    // the expanded keySize
    int expandedKeySize = 32;

    // the expanded key
    unsigned char expandedKey[expandedKeySize];

    string keyHex, plaintextHex;

    // Get user input in hex format
    cout << "Enter 16-byte Cipher Key: ";
    cin >> keyHex;

    cout << "Enter 16-byte Plaintext: ";
    cin >> plaintextHex;

    // the cipher key
    // unsigned char key[16] = {0x11, 0x12, 0x13, 0x14,  // 11121314
    //     0x15, 0x16, 0x17, 0x18,  // 15161718
    //     0x19, 0x20, 0x21, 0x22,  // 19202122
    //     0x23, 0x24, 0x25, 0x26}; // Padding (if needed)

    unsigned char key[16], plaintext[16], ciphertext[16];

    for (size_t i = 0; i < 16; i++)
    {
        key[i] = stoi(keyHex.substr(i * 2, 2), nullptr, 16);
        plaintext[i] = stoi(plaintextHex.substr(i * 2, 2), nullptr, 16);
    }

    // the cipher key size
    keySize size = SIZE_16;

    // the plaintext
    // unsigned char plaintext[16] = {0x01, 0x02, 0x03, 0x04,  // 01020304
    //     0x05, 0x06, 0x07, 0x08,  // 05060708
    //     0x09, 0x10, 0x11, 0x12,  // 09101112
    //     0x13, 0x14, 0x15, 0x16};

    // the ciphertext

    cout << "\nCipher Key (HEX format):\n";
    for (int i = 0; i < 16; i++)
    {
        cout << hex << setw(2) << setfill('0') << (int)key[i] << " ";
    }

    cout << endl;

    // Test the Key Expansion
    expandKey(expandedKey, key, size, expandedKeySize);

    cout << "\nExpanded Key (HEX format):\n";
    for (int i = 0; i < expandedKeySize; i++)
    {
        cout << hex << setw(2) << setfill('0') << (int)expandedKey[i] << ((i + 1) % 16 ? ' ' : '\n');
    }

    cout << "\nPlaintext (HEX format):\n";
    for (int i = 0; i < 16; i++)
    {
        cout << hex << setw(2) << setfill('0') << (int)plaintext[i] << " ";
    }
    cout << endl;

    // AES Encryption
    aes_encrypt(plaintext, ciphertext, key, SIZE_16);

    cout << "\nCiphertext (HEX format):\n";
    for (int i = 0; i < 16; i++)
    {
        cout << hex << setw(2) << setfill('0') << (int)ciphertext[i] << ((i + 1) % 16 ? ' ' : '\n');
    }

    return 0;
}

unsigned char getSBoxValue(unsigned char num)
{
    return s_box[num];
}

void rotate(unsigned char *word)
{
    unsigned char c = word[0];
    for (int i = 0; i < 3; i++)
        word[i] = word[i + 1];
    word[3] = c;
}

unsigned char getRconValue(unsigned char num)
{
    return Rcon[num];
}

void core(unsigned char *word, int iteration)
{
    // rotate the 32-bit word 8 bits to the left
    rotate(word);

    // apply S-Box substitution on all 4 parts of the 32-bit word
    for (int i = 0; i < 4; ++i)
    {
        word[i] = getSBoxValue(word[i]);
    }

    // XOR the output of the rcon operation with i to the first part (leftmost) only
    word[0] ^= getRconValue(iteration);
}

void expandKey(unsigned char *expandedKey,
               unsigned char *key,
               keySize size,
               size_t expandedKeySize)
{
    // current expanded keySize, in bytes
    size_t currentSize = 0;
    int rconIteration = 1;
    unsigned char t[4] = {0}; // temporary 4-byte variable

    // set the 16,24,32 bytes of the expanded key to the input key
    for (size_t i = 0; i < static_cast<size_t>(size); i++)
    {
        expandedKey[i] = key[i];
    }

    currentSize += static_cast<size_t>(size);

    while (currentSize < expandedKeySize)
    {
        // assign the previous 4 bytes to the temporary value t
        for (size_t i = 0; i < 4; i++)
        {
            t[i] = expandedKey[(currentSize - 4) + i];
        }

        /* every 16,24,32 bytes we apply the core schedule to t
         * and increment rconIteration afterwards
         */
        if (currentSize % size == 0)
        {
            core(t, rconIteration++);
        }

        /* We XOR t with the four-byte block 16,24,32 bytes before the new expanded key.
         * This becomes the next four bytes in the expanded key.
         */
        for (size_t i = 0; i < 4; i++)
        {
            expandedKey[currentSize] = expandedKey[currentSize - size] ^ t[i];
            currentSize++;
        }
    }
}

void subBytes(unsigned char *state)
{
    /* substitute all the values from the state with the value in the SBox
     * using the state value as index for the SBox
     */
    for (int i = 0; i < 16; i++)
    {
        state[i] = getSBoxValue(state[i]);
    }
}

void shiftRows(unsigned char *state)
{
    // iterate over the 4 rows and call shiftRow() with that row
    for (int i = 0; i < 4; i++)
        shiftRow(state + i * 4, i);
}

void shiftRow(unsigned char *state, unsigned char nbr)
{
    // each iteration shifts the row to the left by 1
    for (unsigned char i = 0; i < nbr; i++)
    {
        unsigned char tmp = state[0];
        for (size_t j = 0; j < 3; j++)
            state[j] = state[j + 1];
        state[3] = tmp;
    }
}

void addRoundKey(unsigned char *state, unsigned char *roundKey)
{
    for (int i = 0; i < 16; i++)
        state[i] = state[i] ^ roundKey[i];
}

unsigned char galois_multiplication(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    while (b > 0)
    {
        if ((b & 1) != 0)
        {
            p ^= a;
        }
        bool hi_bit_set = (a & 0x80) != 0;
        a <<= 1;
        if (hi_bit_set)
        {
            a ^= 0x1b;
        }
        b >>= 1;
    }
    return p & 0xFF;
}

void mixColumns(unsigned char *state)
{
    vector<unsigned char> column(4);

    // iterate over the 4 columns
    for (size_t i = 0; i < 4; i++)
    {
        // construct one column by iterating over the 4 rows
        for (size_t j = 0; j < 4; j++)
        {
            column[j] = state[(j * 4) + i];
        }

        // apply the mixColumn on one column
        mixColumn(column.data());

        // put the values back into the state
        for (size_t j = 0; j < 4; j++)
        {
            state[(j * 4) + i] = column[j];
        }
    }
}

void mixColumn(unsigned char *column)
{
    vector<unsigned char> cpy(column, column + 4); // Copy the column values

    column[0] = galois_multiplication(cpy[0], 2) ^
                galois_multiplication(cpy[1], 3) ^
                galois_multiplication(cpy[2], 1) ^
                galois_multiplication(cpy[3], 1);

    column[1] = galois_multiplication(cpy[0], 1) ^
                galois_multiplication(cpy[1], 2) ^
                galois_multiplication(cpy[2], 3) ^
                galois_multiplication(cpy[3], 1);

    column[2] = galois_multiplication(cpy[0], 1) ^
                galois_multiplication(cpy[1], 1) ^
                galois_multiplication(cpy[2], 2) ^
                galois_multiplication(cpy[3], 3);

    column[3] = galois_multiplication(cpy[0], 3) ^
                galois_multiplication(cpy[1], 1) ^
                galois_multiplication(cpy[2], 1) ^
                galois_multiplication(cpy[3], 2);
}

void aes_round(unsigned char *state, unsigned char *roundKey)
{
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, roundKey);
}

void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey)
{
    // iterate over the columns
    for (int i = 0; i < 4; i++)
    {
        // iterate over the rows
        for (int j = 0; j < 4; j++)
        {
            roundKey[(i + (j * 4))] = expandedKey[(i * 4) + j];
        }
    }
}

void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds)
{
    vector<unsigned char> roundKey(16);

    createRoundKey(expandedKey, roundKey.data());
    addRoundKey(state, roundKey.data());

    for (int i = 1; i < nbrRounds + 1; i++)
    {
        createRoundKey(expandedKey + 16 * i, roundKey.data());
        aes_round(state, roundKey.data());
    }
}

char aes_encrypt(unsigned char *input,
                 unsigned char *output,
                 unsigned char *key,
                 enum keySize size)
{
    // the expanded keySize
    int expandedKeySize;

    // the number of rounds
    int nbrRounds = 1;

    // the 128 bit block to encode
    vector<unsigned char> block(16);

    expandedKeySize = (16 * (nbrRounds + 1));

    vector<unsigned char> expandedKey(expandedKeySize);
    for (int i = 0; i < 4; i++)
    {
        // Iterate over the rows
        for (int j = 0; j < 4; j++)
            block[(i + (j * 4))] = input[(i * 4) + j];
    }

    // Expand the key into a 176, 208, or 240-byte key
    expandKey(expandedKey.data(), key, size, expandedKeySize);

    // Encrypt the block using the expanded key
    aes_main(block.data(), expandedKey.data(), nbrRounds);

    // Unmap the block again into the output
    for (int i = 0; i < 4; i++)
    {
        // Iterate over the rows
        for (int j = 0; j < 4; j++)
            output[(i * 4) + j] = block[(i + (j * 4))];
    }

    return SUCCESS;
}