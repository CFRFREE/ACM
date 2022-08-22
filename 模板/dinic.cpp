#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int s, t, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N];
queue<int> q;

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
	while (q.size())
		q.pop();
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
void work()
{
	int n = read(), m = read();
	s = read(), t = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z);
	}
	LL maxflow = 0;
	while (bfs())
	{
		int tep;
		while (tep = dinic(s, INF))
			maxflow += tep;
	}
	printf("%lld\n", maxflow);
	return;
}
signed main()
{
	work();
}