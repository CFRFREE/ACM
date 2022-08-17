#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 5005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int a[N][N], c[N][N];
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
void work()
{
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			a[i][j] = read();
			c[i][j] = 0;
		}
	for (int j = 1; j <= m; j++)
		for (int i = 1; i <= n; i++)
		{
			if (a[i][j] >= a[i - 1][j])
				c[i][j] = c[i - 1][j] + 1;
			else
				c[i][j] = 1;
		}
	int ans = 0;
	stack<int>s;
	for (int i = 1; i <= n; i++)
	{
		vector<int>val(m + 2), L(m + 2), R(m + 2);
		for (int j = 1; j <= m; j++)
			val[j] = c[i][j];
		val[0] = val[m + 1] = 0;
		while (s.size())s.pop();
		for (int j = 0; j <= m + 1; j++)
		{
			while (s.size() && val[s.top()] >= val[j])
				s.pop();
			if (s.size())
				L[j] = s.top();
			s.push(j);
		}
		while (s.size())s.pop();
		for (int j = m + 1; j >= 0; j--)
		{
			while (s.size() && val[s.top()] >= val[j])
				s.pop();
			if (s.size())
				R[j] = s.top();
			s.push(j);
		}
		for (int j = 1; j <= m; j++)
			ans = max(ans, val[j] * (R[j] - L[j] - 1));
	}
	printf("%d\n", ans);
}
signed main()
{
	int T = 1; cin >> T;
	while ( T-- )
		work();
	return 0;
}