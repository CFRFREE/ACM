#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 1005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int n, m, vis[N], cnt[N], f[N];
double d[N];
vector<pair<int, double> >a[N];
vector<pair<pii, int> >e;
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
int ok(double now)
{
	stack<int>q;
	for (int i = 1; i <= n; i++)
	{
		vis[i] = cnt[i] = 0;
		d[i] = INF;
		q.push(i);
	}
	while (q.size())
	{
		int x = q.top();
		q.pop();
		vis[x] = 0;
		if (cnt[x] >= n)
			return 1;
		for (auto [y, z] : a[x])
		{
			double val = now * z - f[y];
			if (d[x] + val < d[y])
			{
				d[y] = d[x] + val;
				cnt[y]++;
				if (!vis[y])
					q.push(y);
				vis[y] = 1;
			}
		}
	}
	return 0;
}
signed main()
{
	n = read(), m = read();
	e.resize(m);
	for (int i = 1; i <= n; i++)
		f[i] = read();
	for (int i = 0; i < m; i++)
	{
		int x = read(), y = read(), z = read();
		a[x].emplace_back(y, z);
	}
	double L = 0.0, R = 1000.0, eps = 1e-4;
	double ans = 0;
	for (int i = 1; i <= 30; i++)
	{
		double mid = (L + R) / 2.0;
		if (ok(mid))
		{
			ans = max(ans, mid);
			L = mid;
		}
		else
			R = mid;
	}
	printf("%.2f\n", ans);
	return 0;
}