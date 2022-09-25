#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define int long long
#define endl '\n'
#define N 105
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
		cost[i] = read(), cost[i] += cost[i - 1];
	for (int i = 1; i <= n; i++)
		w[i] = read(), sum[i] = sum[i - 1] + w[i];
	auto get_sum = [&](int L, int R) {
		return sum[R] - sum[L - 1];
	};
	memset(dp, -0x3f, sizeof(dp));
	dp[0][0][0][0][0] = 0;
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int a = 0; a * 2 <= i + 1; a++)
			for (int b = 0; a * 2 + b * 3 <= i + 1; b++)
				for (int c = 0; a * 2 + b * 3 + c * 4 <= i + 1; c++)
					for (int d = 0; a * 2 + b * 3 + c * 4 + d * 5 <= i + 1; d++)
					{
						if (a * cost[1] + b * cost[2] + c * cost[3] + d * cost[4] > T)
							continue;
						dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 1][a][b][c][d]);
						if (i - 2 >= 0 && a - 1 >= 0)
							dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 2][a - 1][b][c][d] + get_sum(i - 1, i - 1));
						if (i - 3 >= 0 && b - 1 >= 0)
							dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 3][a][b - 1][c][d] + get_sum(i - 2, i - 1));
						if (i - 4 >= 0 && c - 1 >= 0)
							dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 4][a][b][c - 1][d] + get_sum(i - 3, i - 1));
						if (i - 5 >= 0 && d - 1 >= 0)
							dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 5][a][b][c][d - 1] + get_sum(i - 4, i - 1));
						if (i == n)
						{
							if (i - 1 >= 0 && a - 1 >= 0)
								dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 1][a - 1][b][c][d] + get_sum(i, i));
							if (i - 2 >= 0 && b - 1 >= 0)
								dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 2][a][b - 1][c][d] + get_sum(i - 1, i));
							if (i - 3 >= 0 && c - 1 >= 0)
								dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 3][a][b][c - 1][d] + get_sum(i - 2, i));
							if (i - 4 >= 0 && d - 1 >= 0)
								dp[i][a][b][c][d] = max(dp[i][a][b][c][d], dp[i - 4][a][b][c][d - 1] + get_sum(i - 3, i));
						}
						ans = max(ans, dp[i][a][b][c][d]);
					}
	printf("%lld\n", ans);
}
signed main()
{
	work();
	return 0;
}