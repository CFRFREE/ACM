#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 500005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N];
vector<int> ans[N];
struct Node
{
	int from, to, min, max;
} e[N];

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
inline void addage(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
inline void add(int x, int y, int mini, int maxn)
{
	addage(x, y, maxn - mini);
	addage(y, x, 0);
}
int bfs()
{
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(S);
	d[S] = 1;
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				q.push(y);
				d[y] = d[x] + 1;
				if (y == T)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == T)
		return flow;
	int k, rest = flow;
	for (int i = from[x]; i && rest; i = Next[i])
	{
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(rest, val[i]));
			if (!k)
				d[y] = 0;
			val[i] -= k;
			val[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int dinic()
{
	int res = 0;
	while (bfs())
	{
		int tep = 0;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read();
	vector<int> delta(n + 1);
	S = 0, T = n + 1;
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read(), d = read();
		add(a, b, c, d);
		e[i] = {a, b, c, d};
		delta[a] -= c;
		delta[b] += c;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
		if (delta[i] > 0)
		{
			sum += delta[i];
			add(S, i, 0, delta[i]);
		}
		else if (delta[i] < 0)
			add(i, T, 0, -delta[i]);
	int maxflow = dinic();
	if (maxflow != sum)
	{
		puts("NO");
		return;
	}
	puts("YES");
	for (int i = 1; i <= m; i++)
		printf("%d\n", e[i].min + val[i << 1 | 1]);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}