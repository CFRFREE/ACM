#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 100005
using namespace std;
int a[N], id[N], L[N], R[N], sum[N], lazy[N];
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
signed main()
{
    int n = read(), m = read();
    int len = sqrt(n);
    int tot = (n + len - 1) / len;
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += a[i];
    }
    for (int i = 1; i <= tot; i++)
    {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
    }
    while (m--)
    {
        int p = read();
        if (p == 1)
        {
            int x = read(), y = read(), z = read();
            if (id[x] == id[y])
                for (int i = x; i <= y; i++)
                    a[i] += z, sum[id[i]] += z;
            else
            {
                for (int i = x; i <= R[id[x]]; i++)
                    a[i] += z, sum[id[i]] += z;
                for (int i = L[id[y]]; i <= y; i++)
                    a[i] += z, sum[id[i]] += z;
                for (int i = id[x] + 1; i <= id[y] - 1; i++)
                    lazy[i] += z;
            }
        }
        else
        {
            int x = read(), y = read();
            int s = 0;
            if (id[x] == id[y])
                for (int i = x; i <= y; i++)
                    s += a[i] + lazy[id[i]];
            else
            {
                for (int i = x; i <= R[id[x]]; i++)
                    s += a[i] + lazy[id[i]];
                for (int i = L[id[y]]; i <= y; i++)
                    s += a[i] + lazy[id[i]];
                for (int i = id[x] + 1; i <= id[y] - 1; i++)
                    s += sum[i] + lazy[i] * len;
            }
            printf("%lld\n", s);
        }
    }
    return 0;
}