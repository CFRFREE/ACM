#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define endl '\n'
#define N 5005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int d[N];
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
	int n = read(), m = read();
	vector<int>vis(n + 1);
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		a[x].emplace_back(y, z);
		a[y].emplace_back(x, z);
	}
	memset(d, 0x7f, sizeof(d));
	d[1] = 0;
	int cnt = 0;
	int ans = 0;
	priority_queue<pair<int, int> >q;
	q.push({0, 1});
	while (q.size() && cnt < n)
	{
		auto [val, x] = q.top();
		q.pop();
		if (vis[x])continue;
		vis[x] = 1;
		cnt++;
		ans += -val;
		for (auto [y, z] : a[x])
			if (d[y] > z)
			{
				d[y] = z;
				if (!vis[y])
					q.push({ -d[y], y});
			}
	}
	if (cnt == n)
		printf("%lld\n", ans);
	else
		puts("orz");
	return 0;
}