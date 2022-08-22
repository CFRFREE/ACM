#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int s, t, cnt = 1;
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
inline void add(int x, int y, int z)
{
	addage(x, y, z);
	addage(y, x, 0);
}
int bfs()
{
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 1;
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
				if (y == t)
					return 1;
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == t)
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
		while (tep = dinic(s, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read();
	vector<int> delta(n + 1);
	s = 0, t = n + m + 1;
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read(), c = read(), d = read();
		add(a, b, d - c);
		e[i] = {a, b, c, d};
		delta[a] -= c;
		delta[b] += c;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
		if (delta[i] > 0)
		{
			sum += delta[i];
			add(s, i, delta[i]);
		}
		else if (delta[i] < 0)
			add(i, t, -delta[i]);
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
}