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

int main()
{
    int H, p, q, e0, r, d;
    cout << "Enter H,p,q,e0,r,d: ";
    cin >> H >> p >> q >> e0 >> r >> d;

    int e1 = static_cast<int>(pow(e0, (p - 1) / q)) % static_cast<int>(p);
    int e2 = static_cast<int>(pow(e1, d)) % static_cast<int>(p);

    int S1 = (static_cast<int>(pow(e1, r)) % p) % q;
    cout << "S1: " << S1 << endl;
    int S2 = ((H + d * S1) * static_cast<int>(pow(r, phi(q) - 1))) % q;
    cout << "S2: " << S2 << endl;
    int invS2 = static_cast<int>(pow(S2, phi(q) - 1)) % q;
    int V = (static_cast<int>(pow(e1, H * invS2)) * static_cast<int>(pow(e2, S1 * invS2)) % p) % q;
    cout << "V: " << V << endl;
    if (V == S2)
    {
        cout << "Signature is valid" << endl;
    }
    else
    {
        cout << "Signature is invalid" << endl;
    }
    return 0;
}