#include <bits/stdc++.h>
using namespace std;

int phi(int n)
{
    int result = n;
    for (int i = 2; i * i < n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
            {
                n = n - n / i;
            }
            result -= result / i;
        }
    }
    if (n > 1)
    {
        result = result - result / n;
    }
    return result;
}

int powMod(int a, int b, int mod)
{
    int result = 1;
    a = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b = b >> 1;
    }
    return result % mod;
}

int modInv(int a, int m)
{
    return (powMod(a, phi(m) - 1, m));
}

int main()
{
    int p, d, q, e0, r, H;
    cout << "Enter H,p,q,e0,r,d: ";
    cin >> H >> p >> q >> e0 >> r >> d;
    int e1 = powMod(e0, (p - 1 / q), p);
    int e2 = powMod(e1, d, p);

    int S1 = powMod(e1, r, p) % q;
    int S2 = ((H + d * S1) * modInv(r, q)) % q;
    cout << "S1: " << S1 << "S2: " << S2 << endl;
    int invS2 = modInv(S2, q);
    int V = ((powMod(e1, H * invS2, p) * powMod(e2, S1 * invS2, p)) % p) % q;
    cout << "V: " << V << endl;
    cout << (V == S1);
    return 0;
}