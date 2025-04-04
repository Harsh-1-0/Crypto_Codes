#include <bits/stdc++.h>
using namespace std;

int phi(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
            {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1)
    {
        result -= result / n;
    }
    return result;
}

int modInverse(int a, int m)
{
    int m0 = m, x0 = 0, x1 = 1;
    if (m == 1)
        return 0;

    while (a > 1)
    {
        int q = a / m;
        int t = m;

        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int modular_pow(int base, int exp, int mod)
{
    int result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (1LL * result * base) % mod;
        }
        base = (1LL * base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main()
{
    int n, e, M, d, p, q;
    int t;

    cout << "Enter 0 for p q or 1 for n: ";
    cin >> t;

    if (!t)
    {
        cout << "Enter p q : ";
        cin >> p >> q;
        n = p * q;
        cout << "n: " << n << endl;
    }
    else
    {
        cout << "Enter n: ";
        cin >> n;
    }

    cout << "Enter e: ";
    cin >> e;
    cout << "Enter M: ";
    cin >> M;
    cout << "Enter 0 for d input else 1: ";
    cin >> t;

    if (t)
    {
        d = modInverse(e, phi(n));
        cout << "Computed d: " << d << endl;
    }
    else
    {
        cout << "Enter d: ";
        cin >> d;
    }

    int signature = modular_pow(M, d, n);
    cout << "Signature: " << signature << endl;

    int verification = modular_pow(signature, e, n);
    if (M == verification)
    {
        cout << "Signature Verified" << endl;
    }
    else
    {
        cout << "Signature Verification Failed" << endl;
    }

    return 0;
}
