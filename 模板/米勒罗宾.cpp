#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 100005
using namespace std;
inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
int qpow(int a, int n, int p)
{
    int ans = 1;
    while (n)
    {
        if (n & 1)
            ans = (__int128)ans * a % p;
        a = (__int128)a * a % p;
        n >>= 1;
    }
    return ans;
}
int is_prime(int x)
{
    if (x < 3)
        return x == 2;
    if (x % 2 == 0)
        return 0;
    int A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, d = x - 1, r = 0;
    while (d % 2 == 0)
        d /= 2, ++r;
    for (auto a : A)
    {
        int v = qpow(a, d, x);
        if (v <= 1 || v == x - 1)
            continue;
        for (int i = 0; i < r; ++i)
        {
            v = (__int128)v * v % x;
            if (v == x - 1 && i != r - 1)
            {
                v = 1;
                break;
            }
            if (v == 1)
                return 0;
        }
        if (v != 1)
            return 0;
    }
    return 1;
}
signed main()
{
    int x = read();
    printf("%lld\n", is_prime(x));
    return 0;
}