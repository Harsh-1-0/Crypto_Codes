#include <bits/stdc++.h>
using namespace std;

vector<unsigned char> addPadding(vector<unsigned char> messageBytes, int originalLength)
{
    int messageBitLength = messageBytes.size() * 8;
    int paddingBits = -(messageBitLength + 64) % 512;
    if (paddingBits < 0)
    {
        paddingBits += 512;
    }
    int totalLength = messageBytes.size() + (paddingBits / 8) + 8;
    vector<unsigned char> paddedMessage(totalLength, 0);
    copy(messageBytes.begin(), messageBytes.end(), paddedMessage.begin());
    paddedMessage[messageBytes.size()] = 0x80;
    long long lengthBits = static_cast<long long>(originalLength);
    for (int i = 0; i < 8; i++)
    {
        paddedMessage[paddedMessage.size() - 1 - i] = (lengthBits >> (i * 8)) & 0xFF;
    }
    return paddedMessage;
}

vector<int> T(64);
void initializeT()
{
    for (int i = 0; i < 64; i++)
    {
        T[i] = static_cast<int>((1LL << 32) * abs(sin(i + 1)));
    }
}

int main()
{
    initializeT();
    string message;
    cout << "Enter message: ";
    getline(cin, message);

    vector<unsigned char> messageBytes(message.begin(), message.end());
    int originalLength = messageBytes.size() * 8;
    vector<unsigned char> paddedMessage = addPadding(messageBytes, originalLength);

    cout << "\nFull Padded Message Structure:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Message bytes (hex):" << endl;
    for (size_t i = 0; i < paddedMessage.size(); i++)
    {
        printf("%02x ", paddedMessage[i]);
        if ((i + 1) % 16 == 0)
            cout << endl;
    }

    cout << "\nBlock Structure (512-bit blocks) - Big Endian:" << endl;
    int blockCount = (paddedMessage.size() * 8) / 512;
    for (int i = 0; i < blockCount; i++)
    {
        cout << "\nBlock " << (i + 1) << " (Words X[0] to X[15]):" << endl;
        for (int j = 0; j < 16; j++)
        {
            int index = i * 64 + j * 4;
            int word = (paddedMessage[index] << 24) |
                       (paddedMessage[index + 1] << 16) |
                       (paddedMessage[index + 2] << 8) |
                       (paddedMessage[index + 3]);
            printf("X[%2d] = %08x ", j, word);
            if ((j + 1) % 4 == 0)
                cout << endl;
        }
    }

    int a = 0x01234567, b = 0x89abcdef, c = 0xfedcba98, d = 0x76543210;
    cout << "\nInitial Hash Values:" << endl;
    printf("a = %08x\n", a);
    printf("b = %08x\n", b);
    printf("c = %08x\n", c);
    printf("d = %08x\n", d);

    cout << "\nProcessing Step 1 of Round 1:" << endl;
    cout << "----------------------------" << endl;

    int X0 = (paddedMessage[0] << 24) | (paddedMessage[1] << 16) |
             (paddedMessage[2] << 8) | paddedMessage[3];
    printf("\nX[0] in big-endian: %08x\n", X0);
    printf("T[0] constant: %08x\n", T[0]);

    int f = (b & c) | (~b & d);
    printf("\nF function calculation:\n");
    printf("(b AND c) = %08x\n", (b & c));
    printf("(NOT b AND d) = %08x\n", (~b & d));
    printf("F = %08x\n", f);

    int sum = a + f;
    printf("\nSum calculation (32-bit overflow):\n");
    printf("%08x + %08x = %08x\n", a, f, sum);
    sum += X0;
    printf("%08x + %08x = %08x\n", a + f, X0, sum);
    sum += T[0];
    printf("%08x + %08x = %08x\n", a + f + X0, T[0], sum);

    int rotated = (sum << 7) | (sum >> (32 - 7));
    printf("\n7-bit left shift calculation:\n");
    printf("Hex value: %08x\n", rotated);

    int newB = b + rotated;
    printf("\nUpdating b: %08x + %08x = %08x\n", b, rotated, newB);

    cout << "\nFinal State After Step 1:" << endl;
    printf("a = %08x\n", d);
    printf("b = %08x\n", newB);
    printf("c = %08x\n", b);
    printf("d = %08x\n", c);

    return 0;
}
