#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int n, m, s, t, cnt = 1, to[N], Next[N], from[N], fy[N], val[N], cost[N], flow[N];
int pre[N], last[N], vis[N];
LL ans_flow, ans_cost;
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
inline void add(int x, int y, int z, int Cost)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
	fy[cnt] = Cost;
}
int spfa()
{
	memset(vis, 0, sizeof(vis));
	memset(cost, 0x7f, sizeof(cost));
	memset(flow, 0x7f, sizeof(flow));
	pre[t] = -1;
	q.push(s);
	vis[s] = 1;
	cost[s] = 0;
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
	return pre[t] != -1;
}
int main()
{
	n = read(), m = read(), s = read(), t = read();
	while (m--)
	{
		int x = read(), y = read(), z = read(), Cost = read();
		add(x, y, z, Cost);
		add(y, x, 0, -Cost);
	}
	while (spfa())
	{
		int x = t;
		ans_flow += flow[t];
		ans_cost += flow[t] * cost[t];
		while (x != s)
		{
			val[last[x]] -= flow[t];
			val[last[x] ^ 1] += flow[t];
			x = pre[x];
		}
	}
	printf("%lld %lld\n", ans_flow, ans_cost);
	return 0;
}