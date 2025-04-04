#include <iostream>
#include <math.h>
using namespace std;
int findPhi(int n)
{
    int result = n; // Initialize result as n
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        { // If i is a divisor of n
            while (n % i == 0)
            {
                n /= i; // Remove all occurrences of i from n
            }
            result -= result / i; // Update result using the formula
        }
    }
    if (n > 1)
    {                         // If n is a prime number greater than 1
        result -= result / n; // Update result using the formula
    }
    return result;
}
int main()
{
    int p, q;
    cout << "Enter p and q: ";
    cin >> p >> q;
    int n = p * q;
    cout << "Enter plain text: ";
    int P;
    cin >> P;
    int phi = (p - 1) * (q - 1);
    cout << "Enter e: ";
    int e;
    cin >> e;
    cout << findPhi(n) << endl;
    int d = static_cast<int>(pow(e, findPhi(phi) - 1)) % static_cast<int>(phi);
    cout << d;
    int encryption = static_cast<int>(pow(P, e)) % n;
    int decryption = static_cast<int>(pow(encryption, d)) % n;
    cout << encryption << endl;
    cout << decryption << endl;
    return 0;
}