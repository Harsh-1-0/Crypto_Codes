#include <bits/stdc++.h>
using namespace std;

// Function to compute GCD
int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

// Function to compute Euler's Totient Function φ(n)
int phi(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// Function to compute (a^b) % mod using Modular Exponentiation
int modExp(int a, int b, int mod)
{
    int result = 1;
    a = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1) // If b is odd, multiply a with result
            result = (result * a) % mod;
        b = b >> 1;        // Divide b by 2
        a = (a * a) % mod; // Square a
    }
    return result;
}

// Function to compute Modular Inverse using Euler's theorem (a^(φ(m)-1) % m)
int modInv(int a, int m)
{
    return modExp(a, phi(m) - 1, m);
}

int main()
{
    int p, q, n, phi_n, e, d, M;

    // Step 1: Input Prime Numbers p and q
    cout << "Enter two prime numbers p and q: ";
    cin >> p >> q;

    // Step 2: Compute n and φ(n)
    n = p * q;
    phi_n = (p - 1) * (q - 1);

    // Step 3: Enter public key exponent e
    cout << "Enter public exponent e (1 < e < phi(n) and coprime with phi(n)): ";
    cin >> e;

    if (gcd(e, phi_n) != 1)
    {
        cout << "e and phi(n) are not coprime. Choose a different e." << endl;
        return 0;
    }

    // Step 4: Compute Private Key d (modular inverse of e mod phi(n))
    d = modInv(e, phi_n);
    cout << "Computed private key d: " << d << endl;

    // Step 5: Enter message M
    cout << "Enter the message (M) to encrypt (0 < M < n): ";
    cin >> M;

    if (M <= 0 || M >= n)
    {
        cout << "Invalid message. It should be between 0 and n-1." << endl;
        return 0;
    }

    // Step 6: Encryption: C = M^e mod n
    int encrypt = modExp(M, e, n);
    cout << "Encrypted message: " << encrypt << endl;

    // Step 7: Decryption: M = C^d mod n
    int decrypt = modExp(encrypt, d, n);
    cout << "Decrypted message: " << decrypt << endl;

    return 0;
}
