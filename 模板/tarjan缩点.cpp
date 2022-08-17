#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int sum[N], scc[N], in[N];
int low[N], dfn[N], w[N], dp[N];
int n, m, cnt, M, ans;
vector<int>a[N], v[N];
stack<int>s;
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
void tarjan(int x)
{
	in[x] = 1;
	s.push(x);
	dfn[x] = low[x] = ++cnt;
	for (auto y : a[x])
	{
		if (!dfn[y])
		{
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if (in[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x])
	{
		M++;
		while (1)
		{
			int X = s.top();
			s.pop();
			scc[X] = M;
			in[X] = 0;
			sum[M] += w[X];
			if (x == X)break;
		}
	}
}
void search(int x)
{
	if (dp[x])return;
	dp[x] = sum[x];
	int maxson = 0;
	for (auto y : v[x])
	{
		if (!dp[y])
			search(y);
		maxson = max(maxson, dp[y]);
	}
	dp[x] += maxson;
}
signed main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		w[i] = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		a[x].push_back(y);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i);
	for (int i = 1; i <= n; i++)
		for (auto y : a[i])
			if (scc[i] != scc[y])
				v[scc[i]].push_back(scc[y]);
	for (int i = 1; i <= M; i++)
		search(i);
	for (int i = 1; i <= M; i++)
		ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}