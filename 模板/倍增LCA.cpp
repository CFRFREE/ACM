#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
int n, m, s, lg[N], dep[N], f[N][22], col[N];
vector<int>a[N];

inline int read()
{
	int X = 0, w = 0; char ch = 0;
	while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

void dfs(int x, int fa)
{
	dep[x] = dep[fa] + 1;
	f[x][0] = fa;
	for (int i = 1; (1 << i) <= dep[x]; i++)
		f[x][i] = f[f[x][i - 1]][i - 1];
	for (auto y : a[x])
		if (y != fa)
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
int getdis(int x, int y)
{
	return dep[x] + dep[y] - 2 * dep[LCA(x, y)];
}
void work()
{
	int n = read(), m = read(), root = read();
	for (int i = 1; i <= n - 1; i++)
	{
		int x = read(), y = read();
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(root, 0);
	while (m--)
	{
		int x = read(), y = read();
		printf("%d\n", LCA(x, y));
	}
}
void init()
{
	for (int i = 1; i < N; i++)
	{
		lg[i] = lg[i - 1];
		if (i == (1 << lg[i - 1]))lg[i]++;
	}
}
int main()
{
	int T = read();
	while (T--)
		work();
	return 0;
}

