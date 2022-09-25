#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define int long long
#define endl '\n'
#define N 15
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int dp[N][N / 2][N / 3][N / 4][N / 5];
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
void work()
{
	int n = read(), T = read();
	vector<int> cost(4 + 10), w(n + 10), sum(n + 10);
	for (int i = 1; i <= 4; i++)
		cost[i] = read();
	for (int i = 1; i <= n; i++)
		w[i] = read();
	int ans = 0;
	for (int i = 0; i < (1 << n); i++)
	{
		int res_ans = 0;
		int res_cost = 0;
		int now = 0;
		int flag = 0;
		vector<int>v(n + 1);
		for (int j = 1; j <= n; j++)
			if ((i >> (j - 1)) & 1)
				v[j] = 1;
			else v[j] = 0;
		// if (i == 59)
		// {
		// 	for (int j = 1; j <= n; j++)
		// 		printf("%lld ", v[j]);
		// 	puts("");
		// }
		for (int j = 1; j <= n; j++)
		{
			if (res_cost <= T && flag == 0)
				ans = max(ans, res_ans);
			if (v[j])
			{
				now++;
				if (now >= 5)
					flag = 1;
				res_ans += w[j];
				res_cost += cost[now];
			}
			else
				now = 0;
		}
		if (res_cost <= T && flag == 0)
			ans = max(ans, res_ans);
	}
	printf("%lld\n", ans);
}
signed main()
{
	work();
	return 0;
}