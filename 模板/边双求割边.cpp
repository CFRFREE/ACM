#include <bits/stdc++.h>
#include <cstdio>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 2000005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int dfn[N], low[N], cnt, gb[N], id[N];
int dcc;
stack<int> S;
vector<int> ans[N];
vector<pii> a[N];
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
	for (auto [y, z] : a[x])
	{
		if (!dfn[y])
		{
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
			if (low[y] > dfn[x])
				gb[z] = 1;
		}
		else if (y != fa)
			low[x] = min(low[x], dfn[y]);
	}
}
void dfs(int x)
{
	id[x] = dcc;
	for (auto [y, z] : a[x])
		if (!gb[z] && !id[y])
			dfs(y);
}
void work()
{
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		a[x].push_back({y, i});
		a[y].push_back({x, i});
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i, 0);
	for (int i = 1; i <= n; i++)
		if (!id[i])
		{
			dcc++;
			dfs(i);
		}
	for (int i = 1; i <= n; i++)
		ans[id[i]].push_back(i);
	printf("%d\n", dcc);
	for (int i = 1; i <= dcc; i++)
	{
		printf("%d ", ans[i].size());
		for (auto x : ans[i])
			printf("%d ", x);
		puts("");
	}
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	work();
	return 0;
}