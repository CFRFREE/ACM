#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define int long long
#define endl '\n'
#define N 500005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int col[N], sz[N], son[N], cnt[N][26], ans[N], dep[N];
int flag, sum, maxn, tot;
char st[N];
vector<int>a[N];
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
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
void dfs1(int x, int fa)
{
	sz[x] = 1;
	dep[x] = dep[fa] + 1;
	for (auto y : a[x])
	{
		if (y == fa)continue;
		dfs1(y, x);
		sz[x] += sz[y];
		if (sz[y] > sz[son[x]])
			son[x] = y;
	}
}
void cal(int x, int fa, int opt)
{
	cnt[dep[x]][st[x] - 'a'] += opt;
	for (auto y : a[x])
		if (y != fa && y != flag)
			cal(y, x, opt);
}
int check(int k)
{
	int p = 0;
	for (int i = 0; i < 26; i++)
		p += (cnt[k][i] % 2);
	return p <= 1;
}
void dfs2(int x, int fa, int opt)
{
	for (auto y : a[x])
		if (y != fa && y != son[x])
			dfs2(y, x, 0);
	if (son[x])
	{
		dfs2(son[x], x, 1);
		flag = son[x];
	}
	cal(x, fa, 1);
	flag = 0;
	for (auto [k, id] : ask[x])
		ans[id] = check(k);
	if (!opt)
		cal(x, fa, -1);
}
void work()
{
	int n = read(), m = read();
	for (int i = 2; i <= n; i++)
	{
		int x = read();
		a[x].push_back(i);
		a[i].push_back(x);
	}
	scanf("%s", st + 1);
	dfs1(1, 0);
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		ask[x].push_back({ y, i });
	}
	dfs2(1, 0, 0);
	for (int i = 1; i <= m; i++)
		if (ans[i])
			puts("Yes");
		else
			puts("No");
}
signed main()
{
	work();
	return 0;
}