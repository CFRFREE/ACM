// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int n, m, e, match[maxn], vis[maxn], x, y, ans;
vector<int>v[maxn];
int find(int x)
{
    for (int i = 0; i < v[x].size(); i++)
    {
        int y = v[x][i];
        if (!vis[y])
        {
            vis[y] = 1;
            if (!match[y] || find(match[y])) {
                match[y] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1; i <= e; i++)
    {
        scanf("%d%d", &x, &y);
        if (x <= n && y <= m)
            v[x].push_back(y);
    }
    for (int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof(vis));
        if (find(i))ans++;
    }
    cout << ans;
}
