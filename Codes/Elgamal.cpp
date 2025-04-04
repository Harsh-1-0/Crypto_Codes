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
    if (n > 0)
    {
        result -= result / n;
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
    return powMod(a, phi(m) - 1, m);
}

int main()
{
    int p, e1, d, r, M;
    cout << "Enter p,e1,d,r,M: ";
    cin >> p >> e1 >> d >> r >> M;
    int e2 = powMod(e1, d, p);
    cout << "e2: " << e2 << endl;
    int c1 = powMod(e1, r, p);
    int c2 = (M * powMod(e2, r, p)) % p;

    cout << "C1: " << c1 << " C2: " << c2 << endl;
    int D = (c2 * powMod(c1, p - 1 - d, p)) % p;
    cout << "D: " << D;
    return 0;
}