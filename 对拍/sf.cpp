#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define int long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
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
	int n = read();
	vector<int> up, mid, low;
	for (int i = 1; i <= n; i++)
		up.push_back(read());
	for (int i = 1; i <= n; i++)
		mid.push_back(read());
	for (int i = 1; i <= n; i++)
		low.push_back(read());
	sort(all(up));
	sort(all(mid));
	sort(all(low));
	int ans = 0;
	for (auto x : mid)
	{
		int L = 0, R = n - 1, pos = 0;
		while (L <= R)
		{
			int tep = (L + R) >> 1;
			if (up[tep] >= x)
				R = tep - 1;
			else
				L = tep + 1, pos = max(pos, tep);
		}
		int num1 = pos;
		L = 0, R = n - 1, pos = R;
		while (L <= R)
		{
			int tep = (L + R) >> 1;
			if (low[tep] > x)
				R = tep - 1, pos = min(pos, tep);
			else
				L = tep + 1;
		}
		int num2 = pos;
		ans += (num1 + 1) * (n - num2);
	}
	printf("%lld\n", ans);
}
signed main()
{
	work();
	return 0;
}