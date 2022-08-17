#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 500005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;

int n, m, s, vis[N], ans[N], fa[N];
vector<int>v[N];
vector<pii>ask[N];

inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))X = X * 10 + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

int find(int x)
{
    if (fa[x] != x)
        fa[x] = find(fa[x]);
    return fa[x];
}

void tarjan(int x)
{
    vis[x] = 1;
    int X = find(x);
    for (auto y : v[x])
    {
        if (vis[y])continue;
        tarjan(y);
        int Y = find(y);
        if (X != Y)fa[Y] = X;
    }
    for (auto [y, id] : ask[x])
        if (vis[y])
            ans[id] = find(y);
}

int main()
{
    n = read(), m = read(), s = read();
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i < n; i++)
    {
        int x = read(), y = read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for (int i = 1; i <= m; i++)
    {
        int x = read(), y = read();
        ask[x].push_back({y, i});
        ask[y].push_back({x, i});
    }
    tarjan(s);
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}

