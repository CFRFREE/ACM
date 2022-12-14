#include <bits/stdc++.h>
#include <cstdio>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int dfn[N], low[N], cnt, gd[N];
vector<int> a[N];
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
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++cnt;
	int son = 0;
	for (auto y : a[x])
	{
		if (!dfn[y])
		{
			tarjan(y, fa);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x] && x != fa)
				gd[x] = 1;
			if (x == fa)
				son++;
		}
		low[x] = min(low[x], dfn[y]);
	}
	if (son >= 2 && x == fa)
		gd[x] = 1;
}
void work()
{
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i, i);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (gd[i])
			ans++;
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		if (gd[i])
			printf("%d ", i);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	work();
	return 0;
}