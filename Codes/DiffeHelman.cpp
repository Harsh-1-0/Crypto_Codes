#include <bits/stdc++.h>
using namespace std;

int modExp(int a, int b, int mod)
{
    a = a % mod;
    int result = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = result * a;
        }
        b = b >> 1;
        a = (a * a) % mod;
    }
    return result % mod;
}

int main()
{
    int P, xa, xb, g;

    cout << "Enter prime number P: ";
    cin >> P;
    cout << "Enter Generator: ";
    cin >> g;
    cout << "Enter private key of alice: ";
    cin >> xa;
    cout << "Enter private key of bob: ";
    cin >> xb;

    int R2 = modExp(g, xb, P);
    int R1 = modExp(g, xa, P);
    cout << "R1: " << R1 << endl;
    cout << "R2: " << R2 << endl;
    int k1 = modExp(R2, xa, P);
    int k2 = modExp(R1, xb, P);
    cout << "Key generated by Alice: " << k1 << endl;
    cout << "Key generated by Bob: " << k2 << endl;

    return 0;
}