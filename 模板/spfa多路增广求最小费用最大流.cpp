#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int to[N], Next[N], from[N], val[N], fy[N];
int cnt = 1, ans_cost, ans_flow;
int vis[N], dis[N];
int S, T;
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
inline void addage(int x, int y, int z, int c)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
	val[cnt] = z;
	fy[cnt] = c;
}
inline void add(int x, int y, int z, int c)
{
	addage(x, y, z, c);
	addage(y, x, 0, -c);
}
int spfa()
{
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	vis[T] = 1;
	dis[T] = 0;
	deque<int> q;
	q.push_back(T);
	while (q.size())
	{
		int x = q.front();
		q.pop_front();
		vis[x] = 0;
		for (int i = from[x]; i; i = Next[i])
		{
			if (val[i ^ 1] <= 0)
				continue;
			int y = to[i];
			if (dis[y] > dis[x] - fy[i])
			{
				dis[y] = dis[x] - fy[i];
				if (vis[y] == 0)
				{
					vis[y] = 1;
					if (q.size() && dis[y] < dis[q.front()])
						q.push_front(y);
					else
						q.push_back(y);
				}
			}
		}
	}
	return dis[S] != dis[N - 1];
}
int dfs(int x, int flow)
{
	if (x == T)
	{
		vis[T] = 1;
		return flow;
	}
	int used = 0;
	vis[x] = 1;
	for (int i = from[x]; i; i = Next[i])
	{
		int y = to[i];
		if (vis[y] == 0 && val[i] > 0 && dis[x] - fy[i] == dis[y])
		{
			int tep = dfs(y, min(val[i], flow - used));
			if (tep > 0)
			{
				ans_cost += tep * fy[i];
				val[i] -= tep;
				val[i ^ 1] += tep;
				used += tep;
			}
			if (used == flow)
				break;
		}
	}
	return used;
}
void costflow()
{
	ans_cost = 0;
	ans_flow = 0;
	while (spfa())
	{
		vis[T] = 1;
		while (vis[T])
		{
			memset(vis, 0, sizeof(vis));
			ans_flow += dfs(S, INF);
		}
	}
}
void work()
{
	int n = read(), m = read();
	S = read(), T = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read(), c = read();
		add(x, y, z, c);
	}
	costflow();
	printf("%d %d\n", ans_flow, ans_cost);
	// for (int i = 2; i <= cnt; i += 2)
	// {
	// 	val[i] += val[i ^ 1];
	// 	val[i ^ 1] = 0;
	// 	fy[i] = -fy[i];
	// 	fy[i ^ 1] = -fy[i ^ 1];
	// }
	// costflow();
	// printf("%d\n", -ans_cost);
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	work();
	return 0;
}