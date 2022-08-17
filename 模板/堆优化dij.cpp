#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 200005
using namespace std;
int vis[N], d[N];
vector<pair<int, int> >a[N];
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
signed main()
{
	int n = read(), m = read(), s = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		a[x].emplace_back(y, z);
	}
	memset(d, 0x3f, sizeof(d));
	d[s] = 0;
	priority_queue<pair<int, int> >q;
	q.push({0, s});
	while (!q.empty())
	{
		int val = -q.top().first;
		int x = q.top().second;
		q.pop();
		if (vis[x] || val > d[x])continue;
		vis[x] = 1;
		for (auto [y, z] : a[x])
			if (val + z < d[y])
			{
				d[y] = val + z;
				q.push({ -d[y], y});
			}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", d[i]);
	return 0;
}
