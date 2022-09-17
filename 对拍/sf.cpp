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
	int n = read(), k = read(), a = read(), b = read();
	if (a == b)
	{
		puts("YES");
		return;
	}
	if (n <= k)
	{
		puts("NO");
		return;
	}
	if (a > b)
		swap(a, b);
	if (b - a > k)
	{
		puts("YES");
		return;
	}
	if (((n - a > k) || (a - 1 > k)) && ((b - 1 > k) || (n - b > k)))
	{
		puts("YES");
	}
	else
		puts("NO");
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	int T = 1;
	T = read();
	while (T--)
		work();
	return 0;
}