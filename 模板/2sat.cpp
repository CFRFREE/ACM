#include <bits/stdc++.h>
#define INF 2147483647
#define LL long long
#define N 2000005
using namespace std;
int n, m, cnt, dfn[N], low[N], in[N], tot;
int to[N], id[N], next[N], from[N];
stack<int> S;
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
inline void add(int x, int y)
{
    to[+cnt] = y;
    next[cnt] = from[x];
    from[x] = cnt;
}
void tarjan(int x)
{
    dfn[x] = low[x] = ++cnt;
    S.push(x);
    in[x] = 1;
    for (int i = from[x]; i; i = next[i])
    {
        int y = to[i];
        if (!dfn[y])
        {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (in[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (low[x] == dfn[x])
    {
        tot++;
        while (S.top() != x)
        {
            int X = S.top();
            id[X] = tot;
            in[X] = 0;
            S.pop();
        }
        id[S.top()] = tot;
        in[S.top()] = 0;
        S.pop();
    }
}
int main()
{
    n = read(), m = read();
    while (m--)
    {
        int a = read();
        int x = read();
        int b = read();
        int y = read();
        if (x == 0 && y == 0)
        {
            add(a + n, b);
            add(b + n, a);
        }
        if (x == 0 && y == 1)
        {
            add(a + n, b + n);
            add(b, a);
        }
        if (x == 1 && y == 0)
        {
            add(a, b);
            add(b + n, a + n);
        }
        if (x == 1 && y == 1)
        {
            add(a, b + n);
            add(b, a + n);
        }
    }
    cnt = 0;
    for (int i = 1; i <= n << 1; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (id[i] == id[i + n])
        {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    printf("POSSIBLE\n");
    for (int i = 1; i <= n; i++)
        if (id[i] > id[i + n])
            printf("1 ");
        else
            printf("0 ");
    return 0;
}
