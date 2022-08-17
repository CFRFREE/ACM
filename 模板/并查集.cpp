#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 200005
using namespace std;
namespace UF {
int fa[N], rank[N];
inline void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        rank[i] = 1;
    }
}
int find(int x)
{
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
inline void merge(int i, int j)
{
    int x = find(i), y = find(j);
    if (rank[x] <= rank[y])
        fa[x] = y;
    else
        fa[y] = x;
    if (rank[x] == rank[y] && x != y)
        rank[y]++;
}
inline bool same(int i, int j)
{
    return find(i) == find(j);
}
} // namespace UF
inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
int main()
{
    int n = read(), m = read();
    UF::init(n);
    while (m--)
    {
        int opt = read(), x = read(), y = read();
        if (opt == 1)
            UF::merge(x, y);
        else
        {
            if (UF::same(x, y))
                printf("Y\n");
            else
                printf("N\n");
        }
    }
    return 0;
}