#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 500005
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;
int a, b, c, d, k;
int vis[N], mu[N], sum[N];
vector<int> prime;
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
void init(int n)
{
	vis[1] = 1;
	mu[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!vis[i])
			prime.push_back(i), mu[i] = -1;
		for (auto x : prime)
		{
			if (x * i > n)
				break;
			vis[x * i] = 1;
			if (i % x == 0)
				break;
			mu[x * i] = -mu[i];
		}
	}
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + mu[i];
}
int get(int a, int b)
{
	int res = 0;
	for (int L = 1, R; L <= min(a, b); L = R + 1)
	{
		R = min(a / (a / L), b / (b / L));
		res += (sum[R] - sum[L - 1]) * ((a / k) / L) * ((b / k) / L);
	}
	return res;
}
void work()
{
	a = read(), b = read(), c = read(), d = read(), k = read();
	printf("%d\n", get(b, d) - get(a - 1, d) - get(b, c - 1) + get(a - 1, c - 1));
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	init(N - 1);
	int T = read();
	while (T--)
		work();
	return 0;
}