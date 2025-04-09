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
            result = result - result / i;
        }
    }
    if (n > 1)
    {
        result = result - result / n;
    }
    return result;
}

int expoMod(int a, int b, int mod)
{
    a = a % mod;
    int result = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result * a) % mod;
        }
        b = b / 2;
        a = (a * a) % mod;
    }
    return result;
}

int modInv(int a, int m)
{
    return (a, phi(m) - 1, m);
}

int main()
{
    int p, d, q, e0, r, H;
    cout << "Enter H,p,q,e0,r,d: ";
    int e1 = expoMod(e0, (p - 1) / q, p);
    int e2 = expoMod(e1, d, p);

    int S1 = expoMod(e1, r, p) % q;
    int S2 = ((H + d * S1) * modInv(r, q)) % q;

    int invS2 = modInv(S2, q);

    int V = ((expoMod(e1, H * invS2, p) * expoMod(e2, S1 * invS2, p)) % p) % q;
    cout << V << endl;
    return 0;
}