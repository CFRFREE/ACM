#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int S, T, cnt = 1, to[N], Next[N], from[N], fy[N], val[N], cost[N], flow[N];
int pre[N], last[N], vis[N];
LL ans_flow, ans_cost;
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
inline void addage(int x, int y, int z, int Cost)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
	fy[cnt] = Cost;
}
void add(int x, int y, int z, int Cost)
{
	addage(x, y, z, Cost);
	addage(y, x, 0, -Cost);
}
int spfa()
{
	memset(vis, 0, sizeof(vis));
	memset(cost, 0x7f, sizeof(cost));
	memset(flow, 0x7f, sizeof(flow));
	pre[T] = -1;
	q.push(S);
	vis[S] = 1;
	cost[S] = 0;
	while (q.size())
	{
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for (int i = from[x]; i; i = Next[i])
		{
			int y = to[i];
			if (val[i] && cost[x] + fy[i] < cost[y])
			{
				cost[y] = cost[x] + fy[i];
				pre[y] = x;
				last[y] = i;
				flow[y] = min(flow[x], val[i]);
				if (!vis[y])
				{
					vis[y] = 1;
					q.push(y);
				}
			}
		}
	}
	return pre[T] != -1;
}
void work()
{
	int n = read(), m = read();
	S = read(), T = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read(), Cost = read();
		add(x, y, z, Cost);
	}
	while (spfa())
	{
		int x = T;
		ans_flow += flow[T];
		ans_cost += flow[T] * cost[T];
		while (x != S)
		{
			val[last[x]] -= flow[T];
			val[last[x] ^ 1] += flow[T];
			x = pre[x];
		}
	}
	printf("%lld %lld\n", ans_flow, ans_cost);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}