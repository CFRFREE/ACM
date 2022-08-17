#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 1000005
using namespace std;
int n, m, s, t, cnt = 1, to[N], from[N], Next[N], d[N], val[N];
int ans;
queue<int>q;
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
inline void add(int x, int y, int z)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
}
int bfs()
{
	memset(d, 0, sizeof(d));
	d[s] = 1;
	while (q.size())q.pop();
	q.push(s);
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
				if (y == t)return 1;
				q.push(y);
			}
		}
	}
	return 0;
}
int dinic(int x, int flow)
{
	if (x == t)return flow;
	int k, rest = flow;
	for (int i = from[x]; i; i = Next[i])
	{
		int y = to[i];
		if (val[i] && d[y] == d[x] + 1)
		{
			k = dinic(y, min(rest, val[i]));
			if (!k)d[y] = 0;
			rest -= k;
			val[i] -= k;
			val[i ^ 1] += k;
		}
	}
	return flow - rest;
}
int main()
{
	n = read(), m = read();
	s = 0, t = n + 1;
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		if (x)
		{
			add(s, i, 1);
			add(i, s, 0);
		}
		else
		{
			add(i, t, 1);
			add(t, i, 0);
		}
	}
	while (m--)
	{
		int x = read(), y = read();
		add(x, y, 1);
		add(y, x, 0);
		add(y, x, 1);
		add(x, y, 0);
	}
	while (bfs())
		ans += dinic(0, INF);
	printf("%d\n", ans);
	return 0;
}