#include <bits/stdc++.h>
using namespace std;

// MD5 Non-linear Functions
uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) | (~x & z);
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & z) | (y & ~z);
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z)
{
    return x ^ y ^ z;
}

uint32_t I(uint32_t x, uint32_t y, uint32_t z)
{
    return y ^ (x | ~z);
}

int main()
{
    uint32_t a, b, c, d;
    int round;

    cout << "Enter MD5 registers a, b, c, d (in hex, e.g., 0x67452301):" << endl;
    cin >> hex >> a >> b >> c >> d;

    cout << "Enter round number (1 to 4): ";
    cin >> round;

    uint32_t result = 0;

    switch (round)
    {
    case 1:
        result = F(b, c, d);
        cout << "Round 1 (F): ";
        break;
    case 2:
        result = G(b, c, d);
        cout << "Round 2 (G): ";
        break;
    case 3:
        result = H(b, c, d);
        cout << "Round 3 (H): ";
        break;
    case 4:
        result = I(b, c, d);
        cout << "Round 4 (I): ";
        break;
    default:
        cerr << "Invalid round number. Please enter a number between 1 and 4." << endl;
        return 1;
    }

    cout << "Result = 0x" << hex << setw(8) << setfill('0') << result << endl;
    return 0;
}
