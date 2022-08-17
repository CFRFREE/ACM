#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int fa[N], f[N][20], val[N], lg[N], dep[N], vis[N];
int n, m, cnt;
vector<int>a[N];
pair<int, pii>e[N];
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
int find(int x)
{
	if (x != fa[x])
		fa[x] = find(fa[x]);
	return fa[x];
}
void add(int x, int y)
{
	a[x].push_back(y);
	a[y].push_back(x);
}
void init()
{
	for (int i = 1; i < N; i++)
	{
		lg[i] = lg[i - 1];
		if (i == (1 << lg[i - 1]))lg[i]++;
	}
}
void dfs(int x, int father)
{
	vis[x] = 1;
	dep[x] = dep[father] + 1;
	f[x][0] = father;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		f[x][i] = f[f[x][i - 1]][i - 1];
	for (auto y : a[x])
		if (y != father)
			dfs(y, x);
}
int LCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	while (dep[x] != dep[y])
		x = f[x][lg[dep[x] - dep[y]] - 1];
	if (x == y)return x;
	for (int i = lg[dep[x]]; i >= 0; i--)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}
void kruskal()
{
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		auto [x, y] = e[i].second;
		int z = e[i].first;
		x = find(x), y = find(y);
		if (x == y)continue;
		val[++cnt] = z;
		fa[cnt] = fa[x] = fa[y] = cnt;
		add(x, cnt);
		add(y, cnt);
	}
	for (int i = 1; i <= cnt; i++)
		if (!vis[i])
			dfs(find(i), 0);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	init();
	n = read(), m = read();
	int q = read();
	cnt = n;
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		e[i] = { z, {x, y} };
	}
	kruskal();
	while (q--)
	{
		int x = read(), y = read();
		if (find(x) != find(y))
			puts("-1");
		else
			printf("%d\n", val[LCA(x, y)]);
	}
	return 0;
}