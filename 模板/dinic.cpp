#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 500005
using namespace std;
int S, T, cnt = 1;
int to[N], from[N], Next[N], val[N], d[N], cur[N];
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
	queue<int> q;
	memset(d, 0, sizeof(d));
	d[S] = 1;
	cur[S] = from[S];
	q.push(S);
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && !d[y])
			{
				d[y] = d[x] + 1;
				cur[y] = from[y];
				q.push(y);
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
LL dinic()
{
	LL res = 0;
	while (bfs())
	{
		int tep;
		while (tep = dinic(S, INF))
			res += tep;
	}
	return res;
}
void work()
{
	int n = read(), m = read();
	S = read(), T = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z);
	}
	LL maxflow = dinic();
	printf("%lld\n", maxflow);
	return;
}
signed main()
{
	work();
}