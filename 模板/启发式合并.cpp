#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int sz[N], fa[N];
set<int>rb[N], cb[N];
queue<pii>q;
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
	if (fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}
void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y)return;
	if (cb[x].size() > cb[y].size())
	{
		swap(x, y);
		swap(rb[x], rb[y]);
	}
	fa[x] = y;
	sz[y] += sz[x];
	for (auto tep : cb[x])
	{
		int v = find(tep);
		if (v == y)continue;
		rb[v].erase(x);
		rb[v].insert(y);
		cb[y].insert(v);
		if (rb[v].size() == 1)
			q.push({v, *rb[v].begin()});
	}
	cb[y].erase(x);
}
void work(int num)
{
	int n = read();
	for (int i = 1; i <= n; i++)
	{
		rb[i].clear(), cb[i].clear();
		fa[i] = i;
		sz[i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		int m = read();
		while (m--)
		{
			int x = read();
			rb[i].insert(x);
			cb[x].insert(i);
		}
	}
	for (int i = 1; i <= n; i++)
		if (rb[i].size() == 1)
			q.push({i, *rb[i].begin()});
	while (q.size())
	{
		auto tep = q.front();
		q.pop();
		merge(tep.first, tep.second);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, sz[find(i)]);
	printf("Case #%d: %d\n", num, ans);
}
signed main()
{
	int T = read();
	for (int i = 1; i <= T; i++)
		work(i);
	return 0;
}